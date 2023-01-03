#include <filesystem>
#include <regex>
#include <span>
#include <vector>

using directory_vector = std::vector<std::filesystem::directory_entry>;

void mpi_histo(
		const directory_vector::const_iterator begin_dir,
		const directory_vector::const_iterator end_dir,
		const std::regex& expr,
		std::vector<int>& core_histo,
		std::vector<int>& root_histo);
