#include <fstream>
#include <iostream>
#include <mpi/mpi.h>
#include <vector>

#include "../include/mpi_histo.hpp"

void mpi_histo(
		const directory_vector::const_iterator begin_dir,
		const directory_vector::const_iterator end_dir,
		const std::regex& expr,
		std::vector<int>& core_histo,
		std::vector<int>& root_histo) {
	std::smatch expr_match;
	for (const auto& filename: std::vector(begin_dir, end_dir)) {
		std::ifstream label_file;
		label_file.open(filename.path());
		if(label_file.is_open()) {
			std::string file_content;
			while (getline(label_file, file_content)) {
				std::regex_search(file_content, expr_match, expr);
				if (expr_match.size() > 0) {
					int index = std::stoi(expr_match[0]);
					core_histo[index]++;
				}
			}
		}
		label_file.close();
	}
	MPI_Reduce(core_histo.data(), root_histo.data(), core_histo.size(), 
		MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
}
