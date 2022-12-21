#include <array>
#include <filesystem>
#include <regex>

namespace frankie {
	void histo_from_dir(const std::filesystem::directory_iterator& dir,
		const std::regex& expr, std::array<int, 30>& histo);
}
