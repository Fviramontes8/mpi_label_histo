#include <array>
#include <filesystem>
#include <regex>
#include <span>

using directory_vector = std::vector<std::filesystem::directory_entry>;

namespace frankie {
	void mpi_histo_from_dir(
			const directory_vector::const_iterator begin_dir,
			const directory_vector::const_iterator end_dir,
			const std::regex& expr,
			std::array<int, 30>& core_histo,
			std::array<int, 30>& root_histo);
}
