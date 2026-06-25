#pragma once
#include <chrono>

namespace Sign {
	class Time {
	public:
		static float GetTime() {
			std::chrono::duration<float> elapsed = std::chrono::steady_clock::now() - s_Time;
			return elapsed.count();

		}

	private:
		static std::chrono::high_resolution_clock::time_point s_Time;
	};
}
