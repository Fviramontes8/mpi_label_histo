#include "../include/histo_from_dir.hpp"

#include <fstream>
#include <iostream>

namespace frankie {
	void histo_from_dir(const std::filesystem::directory_iterator& dir,
			const std::regex& expr, std::array<int, 30>& histo) {
		std::smatch expr_match;
		for (const auto& filename: dir) {
			std::ifstream label_file;
			label_file.open(filename.path());
			if(label_file.is_open()) {
				std::string file_content;
				while (getline(label_file, file_content)) {
					std::regex_search(file_content, expr_match, expr);
					if (expr_match.size() > 0) {
						int index = std::stoi(expr_match[0]);
						histo[index]++;
					}
				}
			}
			label_file.close();
		}
	}
}
