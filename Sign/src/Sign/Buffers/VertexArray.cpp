#include "VertexArray.h"

namespace Sign {
	VertexArray::VertexArray()
	{
	}
	void VertexArray::Bind(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> commandList) const
	{
		

		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		for (auto& vb : m_VertexBuffers)
		{
			vb->Bind(commandList);
		}

		if (m_IndexBuffer)
		{
			m_IndexBuffer->Bind(commandList);
		}
	}
	void VertexArray::UnBind() const
	{
	}
	void VertexArray::AddVertexBuffers(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		m_VertexBuffers.push_back(vertexBuffer);
	}
	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		m_IndexBuffer = indexBuffer;
	}
	size_t VertexArray::GetIndexBufferCount() const
	{
		return m_IndexBuffer->GetCount();
	}
}
