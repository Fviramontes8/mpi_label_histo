#include <chrono>

namespace frankie {
	class Timer {
		private: 
			std::chrono::time_point<
				std::chrono::system_clock,
				std::chrono::duration<
					long, std::ratio<1, 1000000000>>> _start;
		public:
			Timer();
			~Timer();
	 };
}
