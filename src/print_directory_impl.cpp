#include <iostream>
#include "../include/print_directory.hpp"

void print_dir(const std::filesystem::directory_iterator& dir) {
	for (const auto& file: dir) {
		std::cout << file.path() << '\n';
	}
}
