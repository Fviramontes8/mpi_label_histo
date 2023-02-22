#include <algorithm>
#include <fstream>

#include "../include/histo_io.hpp"

namespace fenk {
	void write_histo_to_file(
			const std::string& filename,
			const std::vector<int>& v) {
		std::ofstream outfile;
		outfile.open(filename);
		if (outfile.is_open()) {
			std::for_each(
				v.begin(), 
				v.end(),
				[&outfile](const int& x) { 
					outfile << x << ' ';
				}
			);
			outfile.close();
		}
	}
}
