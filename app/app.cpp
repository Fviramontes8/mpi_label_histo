#include <array>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mpi/mpi.h>
#include <span>
#include <ranges>
#include <regex>
#include <vector>

#include "../include/histo_from_dir.hpp"
#include "../include/mpi_histo_from_dir.hpp"
#include "../include/timer.hpp"

void print_dir(const std::filesystem::directory_iterator& dir) {
	for (const auto& file: dir) {
		std::cout << file.path() << '\n';
	}
}

int main(int argc, char* argv[])  {
	MPI_Init(&argc, &argv);
	const std::filesystem::path current_dir = std::filesystem::current_path();
	const std::filesystem::path label_path = current_dir/"labels";
	const std::filesystem::directory_iterator label_dir{label_path};
	const std::filesystem::directory_iterator label_dir_copy{label_path};
	const std::vector<std::filesystem::directory_entry> files_in_dir(
		begin(label_dir_copy), end(label_dir_copy)
	);
	const std::regex expr{"([0-9]{1,2}+)"};

	int proc, num_procs;
	MPI_Comm_rank(MPI_COMM_WORLD, &proc);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	int iter_bound = files_in_dir.size() / num_procs;
	const int start_idx = iter_bound * proc;

	std::array<int, 30> histo;
	std::array<int, 30> mpi_core_histo;
	std::array<int, 30> mpi_root_histo;
	std::ranges::for_each(histo, [](int& x) { x=0; });
	std::ranges::for_each(mpi_core_histo, [](int& x) { x=0; });
	std::ranges::for_each(mpi_root_histo, [](int& x) { x=0; });

	{
		frankie::Timer t;
		histo_from_dir(label_dir, expr, histo);
	}
	if (proc == 0) {
		std::cout << "Naive histo:\n\t"; 
		std::ranges::for_each(
			histo,
			[](const int& x) {
				std::cout << x << ' ';
			}
		);
		std::cout << '\n';
	}

	if ((iter_bound % num_procs != 0) && (proc == (num_procs-1))) {
		iter_bound += (iter_bound % num_procs) + 1;
	}

	{
		frankie::Timer t;
		mpi_histo_from_dir(
			files_in_dir.begin() + start_idx,
			files_in_dir.begin() + start_idx + iter_bound,
			expr, 
			mpi_core_histo,
			mpi_root_histo
		);
	}
	if (proc == 0) {
		std::cout << "MPI histo:\n\t";
		std::ranges::for_each(
			mpi_root_histo,
			[](const int& x) {
			std::cout << x << ' ';
			}
		);
		std::cout << '\n';

		std::ofstream outfile;
		outfile.open("histo_data.txt");
		if (outfile.is_open()) {
			std::ranges::for_each(
				histo, 
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
