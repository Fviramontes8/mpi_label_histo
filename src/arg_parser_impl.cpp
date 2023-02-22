#include <iostream>
#include <mpi/mpi.h>

#include "../include/arg_parser.hpp"

namespace fenk {
	po::variables_map parse_options(int argc, char* argv[]) {
		int proc;
		MPI_Comm_rank(MPI_COMM_WORLD, &proc);

		po::options_description desc("Permitted options");
		desc.add_options()
			("help,h", "Show the help message")
			("path,p", po::value<std::string>(), "Required path to directory to calculate histogram, it should be relative to the executable path")
			("size,s", po::value<int>(), "Size of histogram, typically the number of classes in dataset")
			("outfile,o", po::value<std::string>(), "Filename (.txt) where resulting histogram will be stored");

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
		if (vm.count("help")) {
			if (proc == 0) {
				std::cout << desc << '\n';
			}
		}
		return vm;
	}

	HistoArgs parse_arguments(const po::variables_map& vm) {
		int proc;
		MPI_Comm_rank(MPI_COMM_WORLD, &proc);

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

		return HistoArgs{
			label_path,
			vm["size"].as<int>(),
			outfile_name
		};
	}
	
}
