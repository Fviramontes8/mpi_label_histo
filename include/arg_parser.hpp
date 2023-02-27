#include <boost/program_options.hpp>
#include <filesystem>
#include <string>

namespace po = boost::program_options;

namespace fenk {
	struct histo_args {
		std::filesystem::path file_path;
		int histo_size;
		std::string outfile;
	};

	using HistoArgs = struct histo_args;

	po::variables_map parse_options(int argc, char* argv[]);
	HistoArgs parse_arguments(const po::variables_map& vm);
}
