#pragma once
#include <numbers>
#include <random>
#include "Sign/Math/Vector3D.h"

namespace MathUtils {
	inline auto PI = std::numbers::pi_v<float>;

	inline float ConvertToRadians(float degrees)
	{
		return degrees * (PI / 180.0f);
	}

	inline Sign::Vector3D ConvertToRadiansVec3(const Sign::Vector3D& vec)
	{
		return Sign::Vector3D(ConvertToRadians(vec.x), ConvertToRadians(vec.y), ConvertToRadians(vec.z));
	}
	inline float ConvertToDegrees(float radians)
	{
		return radians * (180.0f / PI);
	}
	inline Sign::Vector3D ConvertToDegreesVec3(const Sign::Vector3D& vec)
	{
		return Sign::Vector3D(ConvertToDegrees(vec.x), ConvertToDegrees(vec.y), ConvertToDegrees(vec.z));
	}
	inline float Random_Float(float min, float max) {
		thread_local std::random_device rd;
		thread_local std::mt19937 gen(rd());

		std::uniform_real_distribution<float> distrib(min, max);
		return distrib(gen);
	}

	inline int Random_Int(int min, int max) {
		thread_local std::random_device rd;
		thread_local std::mt19937 gen(rd());

		std::uniform_int_distribution<int> distrib(min, max);
		return distrib(gen);
	}

	inline Sign::Vector3D lerp(const Sign::Vector3D& a, const Sign::Vector3D& b, float t) {
		return { a.x + (b.x - a.x) * t,
				a.y + (b.y - a.y) * t,
				a.z + (b.z - a.z) * t };
	}
	inline float* value_ptr(Sign::Vector3D& vec) 
	{
		return &vec.x;
	}

	inline const float* value_ptr(const Sign::Vector3D& vec) {
		return &vec.x;
	}

/*	inline float* value_ptr(Sign::Quaternion& vec)
	{
		return &vec.x;
	}

	inline const float* value_ptr(const Sign::Quaternion& vec) {
		return &vec.x;
	}*/
}
