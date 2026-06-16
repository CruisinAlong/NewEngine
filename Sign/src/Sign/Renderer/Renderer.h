#pragma once
#include <directx/d3d12.h>
#include <print>
#include "Sign/D3D12Context.h"
#include "Sign/D3D12Utils.h"
#include "Sign/Renderer/Pipeline.h"
#include "Sign/Buffers/VertexArray.h"
#include "Sign/Renderer/Mesh.h"
namespace Sign {
	class Renderer
	{
	public:
		static void Init(D3D12Context* context);
		static void ShutDown();

		static void BeginScene(FLOAT* clearColor);
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const Pipeline& pipeline, const DirectX::XMMATRIX& translation);
		static void EndScene();

		static void OnWindowResize(uint32_t width, uint32_t height);
		static void SetViewPort(uint32_t x, uint32_t y, uint32_t w, uint32_t h);


		static D3D12Context* s_Context;
		static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> s_CommandList;

	private:
		static D3D12_VIEWPORT      s_Viewport;
		static D3D12_RECT          s_ScissorsRect;
	};
}

