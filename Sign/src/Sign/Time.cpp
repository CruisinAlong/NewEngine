#include "Sign/Time.h"

std::chrono::high_resolution_clock::time_point Sign::Time::s_Time = std::chrono::steady_clock::now();