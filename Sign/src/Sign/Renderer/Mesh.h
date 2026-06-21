#pragma once
#include <cstdint>
#include "Sign/Buffers/VertexArray.h"
#include "Sign/Math/SignMath.h"

namespace Sign {
	class Mesh
	{
	public:
		Mesh(const void* vertices, uint32_t vertexCount, const WORD* indices, uint32_t indexCount, 
			const Vector3D& translation,
			const Vector3D& scale,
			const Vector3D& rotation);
		~Mesh() = default;

		const Mat4& GetTransform() const { return m_Transform; }
		const Vector3D& GetTranslation() const { return m_Translation; }
		const Vector3D& GetScale() const { return m_Scale; }
		const Vector3D& GetRotation() const { return m_Rotation; }
		const std::shared_ptr<VertexArray>& GetVertexArray() const { return m_VertexArray; }


		void SetTranslation(const Vector3D& pos) { m_Translation = pos; RecalculateTransform(); }
		void SetScale(const Vector3D& scale) { m_Scale = scale; RecalculateTransform(); };
		void SetRotation(const Vector3D& rotation) { m_Rotation = rotation; RecalculateTransform(); };
	private:
		void RecalculateTransform();
	private:
		Vector3D m_Translation;
		Vector3D m_Scale;
		Vector3D m_Rotation;
		Mat4 m_Transform;

		std::shared_ptr<VertexArray> m_VertexArray;
	};
}

