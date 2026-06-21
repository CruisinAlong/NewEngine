#pragma once
#include "Sign/Math/SignMath.h"
namespace Sign {
	class Camera
	{
	public:
		Camera() = default;
		Camera(const Mat4& projectionMatrix) : m_ProjectionMatrix(projectionMatrix) {}
		virtual ~Camera() = default;

		const Mat4& GetProjectionMatrix() const {return m_ProjectionMatrix;}

	protected:
		Mat4 m_ProjectionMatrix = Mat4::identity();
	};
}

