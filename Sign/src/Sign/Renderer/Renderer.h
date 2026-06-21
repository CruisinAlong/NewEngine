#pragma once
#include <directx/d3d12.h>
#include <print>
#include <memory>	
#include "Sign/D3D12Context.h"
#include "Sign/D3D12Utils.h"
#include "Sign/Renderer/Pipeline.h"
#include "Sign/Buffers/VertexArray.h"
#include "Sign/Buffers/ConstantBuffer.h"
#include "Sign/Renderer/Mesh.h"
#include "PerspectiveCamera.h"
#include "Sign/Math/SignMath.h"

namespace Sign {

	struct CameraData {
		Mat4 viewMatrix;
		Mat4 projectionMatrix;
	};
	class Renderer
	{
	public:
		static void Init(D3D12Context* context);
		static void ShutDown();

		static void BeginScene(FLOAT* clearColor, const PerspectiveCamera& camera);
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const Pipeline& pipeline, const Mat4& translation);
		static void EndScene();

		static void OnWindowResize(uint32_t width, uint32_t height);
		static void SetViewPort(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
		static void CPUSyncToGPU();
		static void Resizebuffers(int width, int height);

		static D3D12Context* s_Context;
		static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> s_CommandList;

	private:
		static D3D12_VIEWPORT      s_Viewport;
		static D3D12_RECT          s_ScissorsRect;
		static std::shared_ptr<ConstantBuffer> m_CameraConstantBuffer;
		static CameraData m_CameraData;
	};
}

