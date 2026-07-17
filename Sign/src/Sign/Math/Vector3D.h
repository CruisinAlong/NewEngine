#pragma once
#include <cmath>
namespace Sign {

	class Vector3D {
	public:
		float x, y, z;


		Vector3D() : x(0), y(0), z(0) {}
		Vector3D(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) {}



		void operator+= (const Vector3D& v) noexcept
		{
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;
		}

		void operator-= (const Vector3D& v)noexcept
		{
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;
		}

		//Addition
		Vector3D operator+ (const Vector3D& v) const noexcept { return Vector3D(this->x + v.x, this->y + v.y, this->z + v.z); }

		//Subtraction
		Vector3D operator- (const Vector3D& v) const noexcept { return Vector3D(this->x - v.x, this->y - v.y, this->z - v.z); }

		//Divide
		Vector3D operator/ (const float v) const noexcept { return Vector3D(this->x / v, this->y / v, this->z / v); }

		//Component Product
		Vector3D operator* (const Vector3D& v) const noexcept { return Vector3D(this->x * v.x, this->y * v.y, this->z * v.z); }

		//Scalar Multiplication
		Vector3D operator* (const float scalarMul) const noexcept { return Vector3D(this->x * scalarMul, this->y * scalarMul, this->z * scalarMul); }

		//Dot Product
		float dotProduct(const Vector3D& v) const noexcept { return ((this->x * v.x) + (this->y * v.y) + (this->z * v.z)); }

		//Vector Product
		Vector3D vectorProduct(const Vector3D& v) const noexcept
		{
			return Vector3D(((this->y * v.z) - (this->z * v.y)),
				((this->z * v.x) - (this->x * v.z)), // Inverted
				((this->x * v.y) - (this->y * v.x)));
		}

		//Magnitude
		float magnitude() const noexcept { return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z); }

		float magnitudeSqrd() const noexcept { return this->x * this->x + this->y * this->y + this->z * this->z; }

		//Direction
		Vector3D normalize() const noexcept
		{
			float mag = magnitude();
			if (mag == 0.0f) return Vector3D(0, 0, 0);
			return Vector3D(this->x / mag, this->y / mag, this->z / mag);
		}

		float distance(const Vector3D& v) const noexcept { return Vector3D(*this - v).magnitude(); }
	};

}

