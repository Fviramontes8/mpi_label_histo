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
#include "../include/arg_parser.hpp"
#include "../include/histo_io.hpp"

int main(int argc, char* argv[])  {
	MPI_Init(&argc, &argv);

	int proc, num_procs;
	MPI_Comm_rank(MPI_COMM_WORLD, &proc);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);


	po::variables_map vm = fenk::parse_options(argc, argv);
	if (vm.count("help")) {
		MPI_Finalize();
		return 0;
	}
	const fenk::HistoArgs args = fenk::parse_arguments(vm);

	const std::filesystem::directory_iterator label_dir{
		args.file_path
	};
	const std::vector<std::filesystem::directory_entry> files_in_dir(
		begin(label_dir), end(label_dir)
	);
	const std::regex expr{"\\d+"};

	int iter_bound = files_in_dir.size() / num_procs;
	const int start_idx = iter_bound * proc;

	std::vector<int> histo(args.histo_size, 0);
	std::vector<int> mpi_core_histo(args.histo_size, 0);
	std::vector<int> mpi_root_histo(args.histo_size, 0);

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
		fenk::write_histo_to_file(args.outfile, mpi_root_histo);
	}

	MPI_Finalize();
	return 0;
}
