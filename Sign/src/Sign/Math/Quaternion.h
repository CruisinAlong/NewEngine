#pragma once
#include "Vector3D.h"
#include <cmath>
namespace Sign {
	class Quaternion {
	public:
		Quaternion() : x(0), y(0), z(0), w(1) {}
		Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		
		static Quaternion QuaternionRotationPitchYawRoll(float pitch, float yaw, float roll) noexcept
		{
			const float halfpitch = pitch * 0.5f;
			float cp = cosf(halfpitch);
			float sp = sinf(halfpitch);

			const float halfyaw = yaw * 0.5f;
			float cy = cosf(halfyaw);
			float sy = sinf(halfyaw);

			const float halfroll = roll * 0.5f;
			float cr = cosf(halfroll);
			float sr = sinf(halfroll);

			return {
					cr * sp * cy + sr * cp * sy,
					cr * cp * sy - sr * sp * cy,
					sr * cp * cy - cr * sp * sy,
					cr * cp * cy + sr * sp * sy
				};
		}
		Quaternion operator*(const Quaternion& q) const noexcept
		{

			return {	(q.w * x) + (q.x * w) + (q.y * z) - (q.z * y),
						(q.w * y) - (q.x * z) + (q.y * w) + (q.z * x),
						(q.w * z) + (q.x * y) - (q.y * x) + (q.z * w),
						(q.w * w) - (q.x * x) - (q.y * y) - (q.z * z)
			};

		}

		//https://fgiesen.wordpress.com/2019/02/09/rotating-a-single-vector-using-a-quaternion/
		Vector3D rotate(const Vector3D& vec) const noexcept
		{
			Vector3D p(x,y,z);
			Vector3D t = p.vectorProduct(vec) * 2.0f;
			return vec + (t*w) + p.vectorProduct(t);
		}
		
		Quaternion Conjugate() const { return { -x,-y,-z,w }; }

	public:
		float x{};
		float y{};
		float z{};
		float w{};
	};
}