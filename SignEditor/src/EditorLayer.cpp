#include "EditorLayer.h"
#include <imgui.h>
#include "ProBuilder/ProBuilderEditorWindow.h"
#include "ProBuilder/ProBuilderTool.h"

namespace Sign {
	EditorLayer::EditorLayer()
	{
		std::println("Editor Layer Created");
	}

	void EditorLayer::OnAttach()
	{
		m_EditorCamera = PerspectiveCamera(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
		m_EditorCamera.SetPerspective(MathUtils::ConvertToRadians(45.0f), 0.1f, 1000.0f);

		FrameBufferSpecifications frameSpecs = {};
		frameSpecs.m_Width = Application::Get().GetWindow().GetWidth();
		frameSpecs.m_Height = Application::Get().GetWindow().GetHeight();
		frameSpecs.m_ColorFormats = { DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R32G32_SINT };
		m_FrameBuffer = std::make_shared<FrameBuffer>(frameSpecs, Renderer::GetContext()->GetDevice().Get());

		Renderer::RegisterFrameBuffers("MainEditorBuffer", m_FrameBuffer);

		/*************** ECS VERSION ********************/
		m_ActiveScene = std::make_shared<Scene>();

		auto CubeECS = m_ActiveScene->CreateEntity("Cube1");
		CubeECS.AddComponent<MeshRendererComponent>(Primitive::Cube3D::Create());
		auto& CubeTransform = CubeECS.GetComponent<TransformComponent>();
		CubeTransform.Translation = { 5.0f,0.0f,5.0f };

		auto CubeECS2 = m_ActiveScene->CreateEntity("Cube2");
		CubeECS2.AddComponent<MeshRendererComponent>(Primitive::Cube3D::Create());
		auto& CubeTransform2 = CubeECS2.GetComponent<TransformComponent>();
		CubeTransform2.Translation = { -5.0f,0.0f,5.0f };

		auto Plane = m_ActiveScene->CreateEntity("Plane");
		Plane.AddComponent<MeshRendererComponent>(Primitive::Plane::Create());
		auto& PlaneTransform = Plane.GetComponent<TransformComponent>();
		PlaneTransform.Scale = { 5.0f,0.0f,5.0f };
		PlaneTransform.Translation = { 0.0f,-0.5f,0.0f };
		/***********************************************/

		/*************** OOP VERSION ********************/
		auto cube = std::make_shared<CubeEntity>();
		cube->SetTranslation({ 0.0f,0.0f,5.0f });
		auto plane = std::make_shared<PlaneEntity>();
		plane->SetTranslation({ 0.0f, -0.5f, 0.0f });

		m_Meshes.push_back(cube);
		m_Meshes.push_back(plane);
		/***********************************************/

		// Create ProBuilder UI/tool
		m_ProBuilderWindow = std::make_unique<ProBuilder::ProBuilderEditorWindow>();
		m_ProBuilderTool = std::make_unique<ProBuilder::ProBuilderTool>();

		std::println("Entity Numbers: {}", m_Meshes.size());
	}

	void EditorLayer::OnDettach()
	{
		m_Meshes.clear();
		m_PendingMeshes.clear();
		m_Meshes.shrink_to_fit();

		m_VertexArray.reset();

		m_ActiveScene.reset();
		m_FrameBuffer.reset();
		m_Shader.reset();

		// Tear down ProBuilder UI/tool
		m_ProBuilderWindow.reset();
		m_ProBuilderTool.reset();
	}

	void EditorLayer::OnUpdate(Timestep dt)
	{
		if (Input::IsKeyPressed(Key::A)) {
			std::println("A");
		}

		if (Input::IsKeyPressed(Key::Esc)) {
			Application::Get().Stop();
		}


		

		m_EditorCamera.OnUpdate(dt);

		for (auto& entity : m_Meshes) {
			if (entity)
				entity->OnUpdate(dt);
		}
	}

	void EditorLayer::OnEvent(Event& event)
	{
		if (event.GetEventType() == EventType::KeyPressed) {
			auto& e = (KeyPressedEvent&)event;
			std::println("{}", (char)e.GetKeyCode());
		}
		EventDispatcher dispatch(event);
		dispatch.Dispatch<WindowResizedEvent>([this](WindowResizedEvent& event) { return OnWindowResizedEvent(event); });
		dispatch.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event) { return OnKeyPressedEvent(event); });
		dispatch.Dispatch<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& event) { return OnMouseButtonPressedEvent(event); });
	}

	void EditorLayer::OnRender()
	{
		if (!m_FrameBuffer) return;

		FLOAT clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

		Renderer::BeginFrame();

		if (FrameBufferSpecifications spec = m_FrameBuffer->GetSpecifications();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
			(spec.m_Width != m_ViewportSize.x || spec.m_Height != m_ViewportSize.y))
		{
			m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_EditorCamera.SetViewPortSize(m_ViewportSize.x, m_ViewportSize.y);
		}

		m_FrameBuffer->TransitionTo(Renderer::GetCommandList().Get(), D3D12_RESOURCE_STATE_RENDER_TARGET);
		m_FrameBuffer->Bind();
		m_FrameBuffer->ClearAttchment(clearColor);

		Renderer::BeginScene(m_EditorCamera);

		for (auto& pending : m_PendingMeshes) {
			const float spawnDistance = 5.0f;
			Vector3D spawnPos = m_EditorCamera.GetPosition() + m_EditorCamera.GetForwardDirection() * spawnDistance;
			auto entity = m_ActiveScene->CreateEntity();
			switch (pending) {
			case PrimitiveType::Cube:
				entity.AddComponent<MeshRendererComponent>(Primitive::Cube3D::Create());
				break;
			case PrimitiveType::Plane:
				entity.AddComponent<MeshRendererComponent>(Primitive::Plane::Create());
				break;
			case PrimitiveType::Cylinder:
				entity.AddComponent<MeshRendererComponent>(Primitive::Cylinder::Create());
				break;
			case PrimitiveType::Sphere:
				entity.AddComponent<MeshRendererComponent>(Primitive::Sphere::Create());
				break;
			case PrimitiveType::Stairs:
				entity.AddComponent<MeshRendererComponent>(Primitive::Stairs::Create());
				break;
			default:
				break;
			}
			entity.GetComponent<TransformComponent>().Translation = spawnPos;
			// TODO: push an EditorCommand that wraps ECS creation if you want undo/redo support
		}
		m_PendingMeshes.clear();

		
		/*******ECS********/
		m_ActiveScene->RenderScene(m_SelectedEntity ? m_SelectedEntity.GetID() : INVALID_ENTITY_ID, m_SelectedFaceID);
		/*****************/



		/*for (auto& mesh : m_Meshes) {
			if (mesh->HasMesh())
				Renderer::Submit(mesh->GetMesh()->GetVertexArray(), *mesh->GetShader(), mesh->GetTransform());
		}*/

		if (m_PickRequest) {
			PixelData pixelData = m_FrameBuffer->ReadPixel(1,(int)m_PickCoords.x, (int)m_PickCoords.y);

			if (pixelData.entityID == -1) {
				std::println("Pixel Data: {}", pixelData.entityID);
				m_SelectedEntity = EntityECS();
				m_SelectedFaceID = -1;
			}
			else {
				EntityID id = (uint32_t)pixelData.entityID;
				m_SelectedEntity = EntityECS(id, m_ActiveScene.get());
				m_SelectedFaceID = pixelData.faceID;
				std::println("Entity: {}", m_SelectedEntity.GetName());
				std::println("FaceID: {}", m_SelectedFaceID);
			}
			m_PickRequest = false;
		}
		
		
		Renderer::EndScene();



	}

	void EditorLayer::OnImGuiRender()
	{
		static int opt_demo_mode = 0;
		static bool opt_demo_mode_changed = false;
		static bool dockSpaceOpen = true;
		bool IsFullscreen = true;
		bool KeepWindowPadding = true;

		ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_None);

		if (opt_demo_mode_changed)
			ImGui::SetNextWindowFocus();

		ImGui::Begin("Examples: Dockspace", &dockSpaceOpen, ImGuiWindowFlags_MenuBar);

		opt_demo_mode_changed = false;
		opt_demo_mode_changed |= ImGui::RadioButton("Basic demo mode", &opt_demo_mode, 0);
		opt_demo_mode_changed |= ImGui::RadioButton("Advanced demo mode", &opt_demo_mode, 1);

		ImGui::SeparatorText("Options");

		if (opt_demo_mode == 0)
		{
			ImGuiDockNodeFlags args = ImGuiDockNodeFlags_None;
			args &= ImGuiDockNodeFlags_PassthruCentralNode;
			ImGui::CheckboxFlags("Flag: PassthruCentralNode", &args, ImGuiDockNodeFlags_PassthruCentralNode);
		}
		else
		{
			ImGuiDockNodeFlags args = ImGuiDockNodeFlags_None;
			ImGui::Checkbox("Fullscreen", &IsFullscreen);
			ImGui::Checkbox("Keep Window Padding", &KeepWindowPadding);
			ImGui::SameLine();
			ImGui::BeginDisabled(!IsFullscreen);
			ImGui::CheckboxFlags("Flag: PassthruCentralNode", &args, ImGuiDockNodeFlags_PassthruCentralNode);
			ImGui::EndDisabled();
			ImGui::CheckboxFlags("Flag: NoDockingOverCentralNode", &args, ImGuiDockNodeFlags_NoDockingOverCentralNode);
			ImGui::CheckboxFlags("Flag: NoDockingSplit", &args, ImGuiDockNodeFlags_NoDockingSplit);
			ImGui::CheckboxFlags("Flag: NoUndocking", &args, ImGuiDockNodeFlags_NoUndocking);
			ImGui::CheckboxFlags("Flag: NoResize", &args, ImGuiDockNodeFlags_NoResize);
			ImGui::CheckboxFlags("Flag: AutoHideTabBar", &args, ImGuiDockNodeFlags_AutoHideTabBar);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Tools")) {
				if (m_ProBuilderWindow)
				{
					bool vis = m_ProBuilderWindow->IsVisible();
					ImGui::MenuItem("ProBuilder", NULL, &vis);
					m_ProBuilderWindow->SetVisible(vis);
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Help"))
			{
				ImGui::TextUnformatted("This demonstrates the use of ImGui::DockSpace() and a simple editor layout.");
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Viewport");
		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();

		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportHovered);
		
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		if (m_FrameBuffer) {
			UINT64 colorAttachment = m_FrameBuffer->GetTextureID();
			ImGui::Image((ImTextureID)colorAttachment, ImVec2(m_ViewportSize.x, m_ViewportSize.y));

			ImVec2 ImageMin = ImGui::GetItemRectMin();
			ImVec2 ImageMax = ImGui::GetItemRectMax();
			m_ViewportBounds[0] = { ImageMin.x, ImageMin.y };
			m_ViewportBounds[1] = { ImageMax.x, ImageMax.y };
		}

		ImGui::End();
		ImGui::PopStyleVar();

		if (m_ProBuilderWindow && m_ProBuilderWindow->IsVisible())
		{
			m_ProBuilderWindow->OnImGuiRender(m_PendingMeshes);
		}
	}

	bool EditorLayer::OnWindowResizedEvent(WindowResizedEvent& e)
	{
		return false;
	}

	bool EditorLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		if (e.IsRepeated())
			return false;

		switch (e.GetKeyCode())
		{
		case Key::Esc:
		{
			Application::Get().Stop();
			break;
		}
		case Key::Spacebar:
		{
			m_PendingMeshes.push_back(PrimitiveType::Cube);
			std::println("Entitiy Number: {}", m_Meshes.size());
			break;
		}
		case Key::Backspace:
		{
			RemoveObjectCommand* command = new RemoveObjectCommand(m_Meshes);
			command->Execute();
			std::println("Entitiy Number: {}", m_Meshes.size());
			m_EditorHistory.Record(command);
			break;
		}
		case Key::Delete:
		{
			DeleteAllCommand* command = new DeleteAllCommand(m_Meshes, m_InitialEntityCount);
			command->Execute();
			std::println("Entitiy Number: {}", m_Meshes.size());
			m_EditorHistory.Record(command);
			break;
		}
		default:
			break;
		}

		bool control = Input::IsKeyPressed(Key::LControl) || Input::IsKeyPressed(Key::RControl);

		if (e.GetKeyCode() == Key::Z && control)
		{
			m_EditorHistory.Undo();
			std::println("Undo");
		}

		return false;
	}
	bool EditorLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		switch (e.GetMouseButton()) 
		{
		case Mouse::RightButton:
		{
			auto [mx, my] = ImGui::GetMousePos();
			mx -= m_ViewportBounds[0].x;
			my -= m_ViewportBounds[0].y;

			Vector2D viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
			
			int mouseX = (int)mx;
			int mouseY = (int)my;

			
			if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y) {
				std::println("mx: {}, my: {}, viewportSize: {}x{}, framebuffer: {}x{}",
					mx, my, viewportSize.x, viewportSize.y,
					m_FrameBuffer->GetSpecifications().m_Width, m_FrameBuffer->GetSpecifications().m_Height);
				m_PickCoords.x = mouseX;
				m_PickCoords.y = mouseY;

				m_PickRequest = true;
				
			}
			break;
		}
		}

		return false;
	}
}