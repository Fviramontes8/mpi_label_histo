#include <algorithm>
#include <boost/program_options.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mpi/mpi.h>
#include <stdexcept>
#include <span>
#include <ranges>
#include <regex>
#include <vector>

#include "../include/mpi_histo.hpp"

namespace po = boost::program_options;

int main(int argc, char* argv[])  {
	MPI_Init(&argc, &argv);

	po::options_description desc("Permitted options");
	desc.add_options()
		("help,h", "Show the help message")
		("path,p", po::value<std::string>(), "Required path to directory to calculate histogram, it should be relative to the executable path")
		("size,s", po::value<int>(), "Size of histogram");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << '\n';
		MPI_Finalize();
		return 1;
	}

	const std::filesystem::path current_dir = std::filesystem::current_path();
	std::filesystem::path label_path;
	if (vm.count("path")) {
		label_path = current_dir/(vm["path"].as<std::string>());
		if (!std::filesystem::exists(label_path)) {
			std::string err_msg = "Path "+label_path.native()+" does not exist";
			MPI_Finalize();
			throw std::invalid_argument(err_msg);
		}
	}
	else {
		MPI_Finalize();
		throw std::invalid_argument("The (--path/-p) command line argument is required");
	}

	if (!vm.count("size")) {
		MPI_Finalize();
		throw std::invalid_argument("The (--size/-s) command line argument is required");
	}

	const int histo_size = vm["size"].as<int>();

	const std::filesystem::directory_iterator label_dir{label_path};
	const std::vector<std::filesystem::directory_entry> files_in_dir(
		begin(label_dir), end(label_dir)
	);
	const std::regex expr{"\\d+"};

	int proc, num_procs;
	MPI_Comm_rank(MPI_COMM_WORLD, &proc);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	int iter_bound = files_in_dir.size() / num_procs;
	const int start_idx = iter_bound * proc;

	std::vector<int> histo(histo_size, 0);
	std::vector<int> mpi_core_histo(histo_size, 0);
	std::vector<int> mpi_root_histo(histo_size, 0);

	if ((iter_bound % num_procs != 0) && (proc == (num_procs-1))) {
		iter_bound += (iter_bound % num_procs) + 1;
	}

	mpi_histo(
		files_in_dir.begin() + start_idx,
		files_in_dir.begin() + start_idx + iter_bound,
		expr, 
		mpi_core_histo,
		mpi_root_histo
	);

	if (proc == 0) {
		std::ofstream outfile;
		outfile.open("histo_data.txt");
		if (outfile.is_open()) {
			std::ranges::for_each(
				mpi_root_histo, 
				[&outfile](const int& x) { 
					outfile << x << ' ';
				}
			);
			outfile.close();
		}
	}

	MPI_Finalize();
	return 0;
}
