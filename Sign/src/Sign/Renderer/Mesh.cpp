#include "Mesh.h"

namespace Sign {
	Mesh::Mesh(const void* vertices, uint32_t vertexCount, const WORD* indices, uint32_t indexCount,
		const Vector3D& translation,
		const Vector3D& scale,
		const Vector3D& rotation)
	{
		m_VertexArray = std::make_shared<VertexArray>();
		m_Translation = translation;
		m_Scale = scale;
		m_Rotation = rotation;
		RecalculateTransform();

		std::shared_ptr<Sign::VertexBuffer> VB;
		std::shared_ptr<Sign::IndexBuffer>  IB;

		VB = std::make_shared<Sign::VertexBuffer>(vertices, vertexCount);
		m_VertexArray->AddVertexBuffers(VB);
		IB = std::make_shared<Sign::IndexBuffer>(indices, indexCount);
		m_VertexArray->SetIndexBuffer(IB);
	}
	void Mesh::RecalculateTransform()
	{
		m_Transform = Mat4::scale(m_Scale)
			* Mat4::rotateX(m_Rotation.x)
			* Mat4::rotateY(m_Rotation.y)
			* Mat4::rotateZ(m_Rotation.z)
			* Mat4::translate(m_Translation);
	}
}