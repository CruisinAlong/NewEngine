#include "ConstantBuffer.h"
#include "Sign/Renderer/Renderer.h"
namespace Sign {
	ConstantBuffer::ConstantBuffer(uint32_t bufferSize, uint32_t heapIndex) : m_HeapIndex(heapIndex)
	{
		m_Size = (bufferSize + 255) & ~255;

		for (int i = 0; i < D3D12Utils::g_NumFrames; i++) {
			m_ConstantBuffer[i] = D3D12Utils::CreateBuffer(Renderer::GetContext()->GetDevice(), m_Size, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12Utils::UploadHeapProps);

			m_ConstantBufferView[i].BufferLocation = m_ConstantBuffer[i]->GetGPUVirtualAddress();
			m_ConstantBufferView[i].SizeInBytes = m_Size;

			uint32_t uniqueHeapIndex = m_HeapIndex + i;
			Renderer::GetContext()->GetDevice()->CreateConstantBufferView(&m_ConstantBufferView[i], Renderer::GetContext()->GetCPUHandleAt(uniqueHeapIndex));

			m_ConstantBuffer[i]->Map(0, nullptr, &m_CpuMappedAddress[i]);
		}

	}
	ConstantBuffer::~ConstantBuffer()
	{
		for (int i = 0; i < D3D12Utils::g_NumFrames; i++) {
			if(m_ConstantBuffer[i])
				m_ConstantBuffer[i]->Unmap(0, nullptr);
		}
	}
	void ConstantBuffer::setData(const void* data, uint32_t size, uint32_t offset)
	{
		auto currentFrame = Renderer::GetContext()->GetCurrentBackBuffer();
		std::memcpy((uint8_t*)m_CpuMappedAddress[currentFrame] + offset, data, size);
	}
}