#include "AppLayer.h"

AppLayer::AppLayer()
{
	std::println("App Layer Created");
}

void AppLayer::OnAttach()
{
	m_EditorCamera = Sign::PerspectiveCamera(Sign::Application::Get().GetWindow().GetWidth(), Sign::Application::Get().GetWindow().GetHeight());
	m_EditorCamera.SetPerspective(MathUtils::ConvertToRadians(45.0f), 0.1f, 1000.0f);

	m_Shader = std::make_shared<Sign::Shader>(L"Shader/VertexShader.hlsl", L"Shader/PixelShader.hlsl");
	Sign::PipelineSpecifications pSpecs = {};
	pSpecs.Shader = m_Shader;
	pSpecs.InputLayout = { { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }, };
	D3D12_RT_FORMAT_ARRAY rtvFormats = {};
	rtvFormats.NumRenderTargets = 1;
	rtvFormats.RTFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	pSpecs.RTVFormats = rtvFormats;
	pSpecs.DepthTest = TRUE;
	pSpecs.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	m_GraphicsPipeline = std::make_unique<Sign::GraphicsPipeline>(Sign::Renderer::GetContext()->GetDevice(), pSpecs);

	VertexPosColor triangleVertices[3] =
	{
		{Sign::Vector3D(0.0,0.5,0.0), Sign::Vector3D(1.0,0.0,0.0)},
		{Sign::Vector3D(0.5,-0.5,0.0), Sign::Vector3D(0.0,1.0,0.0)},
		{Sign::Vector3D(-0.5,-0.5,0.0), Sign::Vector3D(0.0,0.0,1.0)}
	};

	m_VertexArray = std::make_shared<Sign::VertexArray>();

	std::shared_ptr<Sign::VertexBuffer> triangleVB;
	std::shared_ptr<Sign::IndexBuffer> triangleIB;

	triangleVB = std::make_shared<Sign::VertexBuffer>(triangleVertices, _countof(triangleVertices));
	m_VertexArray->AddVertexBuffers(triangleVB);
	triangleIB = std::make_shared<Sign::IndexBuffer>(trianlgeIndices, _countof(trianlgeIndices));
	m_VertexArray->SetIndexBuffer(triangleIB);


/*	auto Cube = std::make_shared<Sign::CubeEntity>();
	Cube->SetScale(Sign::Vector3D(0.5f, 0.5f, 0.5f));
	auto Cube2 = std::make_shared<Sign::CubeEntity>();
	Cube2->SetTranslation({ 0.0f,0.0f,10.0f });
	Cube2->SetScale(Sign::Vector3D(0.5f, 0.5f, 0.5f));*/

	auto plane = std::make_shared<Sign::PlaneEntity>();

	//auto circle = std::make_shared<Sign::CircleEntity>();
	//m_Meshes.push_back(circle);
	//m_Meshes.push_back(Cube);
	//m_Meshes.push_back(Cube2);
	m_Meshes.push_back(plane);
	m_InitialEntityCount++;
	/*for (int i = 0; i < 100; i++) {
		auto Cube = std::make_shared<Sign::CubeEntity>();
		Cube->SetTranslation({ MathUtils::Random_Float(-15.0f,15.0f),MathUtils::Random_Float(-15.0f,15.0f) ,MathUtils::Random_Float(-15.0f,15.0f) });
		Cube->SetScale(Sign::Vector3D(0.5f, 0.5f, 0.5f));
		m_Meshes.push_back(Cube);
	}*/
}

void AppLayer::OnUpdate(Sign::Timestep dt)
{
	//std::println("Delta Time: {} {}", dt.GetSeconds(), dt.GetMilliseconds());

	if (Sign::Input::IsKeyPressed(Sign::Key::A)) {
		std::println("A");
	}

	if (Sign::Input::IsKeyPressed(Sign::Key::Esc)) {
		Sign::Application::Get().Stop();
	}
	
	m_EditorCamera.OnUpdate(dt);
	//std::println("{} {}", Sign::Input::GetMouseX(), Sign::Input::GetMouseY());
}

void AppLayer::OnEvent(Sign::Event& event)
{
	if (event.GetEventType() == Sign::EventType::KeyPressed) {
		auto& e = (Sign::KeyPressedEvent&)event;
		std::println("{}", (char)e.GetKeyCode());
	}
	Sign::EventDispatcher dispatch(event);
	dispatch.Dispatch<Sign::WindowResizedEvent>([this](Sign::WindowResizedEvent& event) {return OnWindowResizedEvent(event); });
	dispatch.Dispatch<Sign::KeyPressedEvent>([this](Sign::KeyPressedEvent& event) {return OnKeyPressedEvent(event); });

}

void AppLayer::OnRender()
{
	FLOAT clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	Sign::Renderer::BeginScene(clearColor, m_EditorCamera);

	//Need for open commandlist, might have to make a separate func for this
	for (auto& pending : m_PendingMeshes) {
		Sign::CreateObjectCommand* command = new Sign::CreateObjectCommand(m_Meshes, Sign::PrimitiveType::Cube);
		command->Execute();
		m_EditorHistory.Record(command);
	}
	m_PendingMeshes.clear();

	Sign::Renderer::Submit(m_VertexArray, *m_GraphicsPipeline, Sign::Mat4::identity());

	for (auto& mesh : m_Meshes) {
		Sign::Renderer::Submit(mesh->GetMesh()->GetVertexArray(), *m_GraphicsPipeline, mesh->GetTransform());
	}

	Sign::Renderer::EndScene();
}

bool AppLayer::OnWindowResizedEvent(Sign::WindowResizedEvent& e)
{
	m_EditorCamera.SetViewPortSize(e.GetWidth(), e.GetHeight());
	return false;
}

bool AppLayer::OnKeyPressedEvent(Sign::KeyPressedEvent& e)
{
	if (e.IsRepeated())
		return false;

	switch (e.GetKeyCode()) 
	{
		case Sign::Key::Esc: 
		{
			Sign::Application::Get().Stop();
			break;
		}
		case Sign::Key::Spacebar: 
		{
			m_PendingMeshes.push_back(Sign::PrimitiveType::Cube);
			std::println("Entitiy Number: {}", m_Meshes.size());
			break;
		}
		case Sign::Key::Backspace:
		{
			Sign::RemoveObjectCommand* command = new Sign::RemoveObjectCommand(m_Meshes);
			command->Execute();
			std::println("Entitiy Number: {}", m_Meshes.size());
			m_EditorHistory.Record(command);
			break;
		}
		case Sign::Key::Delete:
		{
			Sign::DeleteAllCommand* command = new Sign::DeleteAllCommand(m_Meshes, m_InitialEntityCount);
			command->Execute();
			std::println("Entitiy Number: {}", m_Meshes.size());
			m_EditorHistory.Record(command);
		}
	}
	return false;
}
