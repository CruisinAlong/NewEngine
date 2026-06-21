#pragma once
#include <numbers>
namespace MathUtils {
	inline auto PI = std::numbers::pi_v<float>;

	inline float ConvertToRadians(float degrees)
	{
		return degrees * (PI / 180.0f);
	}
}
