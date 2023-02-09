#include <algorithm>
#include <boost/program_options.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mpi/mpi.h>
#include <stdexcept>
#include <regex>
#include <vector>

#include "../include/mpi_histo.hpp"

namespace po = boost::program_options;

int main(int argc, char* argv[])  {
	MPI_Init(&argc, &argv);

	int proc, num_procs;
	MPI_Comm_rank(MPI_COMM_WORLD, &proc);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	po::options_description desc("Permitted options");
	desc.add_options()
		("help,h", "Show the help message")
		("path,p", po::value<std::string>(), "Required path to directory to calculate histogram, it should be relative to the executable path")
		("size,s", po::value<int>(), "Size of histogram")
		("outfile,o", po::value<std::string>(), "Filename (.txt) where resulting histogram will be stored");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		if (proc == 0) {
			std::cout << desc << '\n';
		}
		MPI_Finalize();
		return 0;
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

	std::string outfile_name;
	if (vm.count("outfile")) {
		outfile_name = vm["outfile"].as<std::string>();
	}
	else {
		outfile_name = "histo_data.txt";
	}

	const int histo_size = vm["size"].as<int>();

	const std::filesystem::directory_iterator label_dir{label_path};
	const std::vector<std::filesystem::directory_entry> files_in_dir(
		begin(label_dir), end(label_dir)
	);
	const std::regex expr{"\\d+"};

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
		outfile.open(outfile_name);
		if (outfile.is_open()) {
			std::for_each(
				mpi_root_histo.begin(), 
				mpi_root_histo.end(),
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
