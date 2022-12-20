#include <chrono>
#include <iostream>

#include "../include/timer.hpp"

namespace frankie {
	Timer::Timer() : _start{std::chrono::system_clock::now()} {}

	Timer::~Timer() {
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> dur = (end - _start);
		std::cout << "Duration: " << dur.count() << '\n';
	}
}
