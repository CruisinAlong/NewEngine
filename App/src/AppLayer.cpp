#include "AppLayer.h"

AppLayer::AppLayer()
{
	std::println("App Layer Created");
}

void AppLayer::OnAttach()
{
	m_Shader = std::make_shared<Sign::Shader>(L"D:/Github/GDENG03/NewEngine/Sign/src/Sign/Shader/VertexShader.hlsl", L"D:/Github/GDENG03/NewEngine/Sign/src/Sign/Shader/PixelShader.hlsl");
	Sign::PipelineSpecifications pSpecs = {};
	pSpecs.Shader = m_Shader;
	pSpecs.Topology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	pSpecs.InputLayout = { { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }, };
	D3D12_RT_FORMAT_ARRAY rtvFormats = {};
	rtvFormats.NumRenderTargets = 1;
	rtvFormats.RTFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	pSpecs.RTVFormats = rtvFormats;
	pSpecs.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	m_GraphicsPipeline = std::make_unique<Sign::GraphicsPipeline>(Sign::Renderer::s_Context->GetDevice(), pSpecs);

	VertexPosColor triangleVertices[3] =
	{
		{DirectX::XMFLOAT3(0.0,0.5,0.0), DirectX::XMFLOAT3(1.0,0.0,0.0)},
		{DirectX::XMFLOAT3(0.5,-0.5,0.0), DirectX::XMFLOAT3(0.0,1.0,0.0)},
		{DirectX::XMFLOAT3(-0.5,-0.5,0.0), DirectX::XMFLOAT3(0.0,0.0,1.0)}
	};

	m_VertexArray = std::make_shared<Sign::VertexArray>();

	std::shared_ptr<Sign::VertexBuffer> triangleVB;
	std::shared_ptr<Sign::IndexBuffer> triangleIB;

	triangleVB = std::make_shared<Sign::VertexBuffer>(triangleVertices, _countof(triangleVertices));
	m_VertexArray->AddVertexBuffers(triangleVB);
	triangleIB = std::make_shared<Sign::IndexBuffer>(trianlgeIndices, _countof(trianlgeIndices));
	m_VertexArray->SetIndexBuffer(triangleIB);


	auto fenceValue = Sign::Renderer::s_Context->GetCommandQueue()->ExecuteCommandList(Sign::Renderer::s_CommandList);
	Sign::Renderer::s_Context->GetCommandQueue()->WaitForFenceValue(fenceValue);
}

void AppLayer::OnUpdate(float ts)
{
	if (Sign::Input::IsKeyPressed(Sign::Key::A)) {
		std::println("A");
	}
	
	//std::println("{} {}", Sign::Input::GetMouseX(), Sign::Input::GetMouseY());
}

void AppLayer::OnEvent(Sign::Event& event)
{
	if (event.GetEventType() == Sign::EventType::KeyPressed) {
		auto& e = (Sign::KeyPressedEvent&)event;
		std::println("{}", (char)e.GetKeyCode());
	}
}

void AppLayer::OnRender()
{
	FLOAT clearColor[] = { 0.4f, 0.6f, 0.9f, 1.0f };
	Sign::Renderer::BeginScene(clearColor);
	Sign::Renderer::Submit(m_VertexArray, *m_GraphicsPipeline, DirectX::XMMatrixIdentity());
	Sign::Renderer::EndScene();
}
