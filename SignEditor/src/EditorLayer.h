#pragma once
#include <Sign.h>
// Forward declare probuilder types to avoid coupling headers here
namespace ProBuilder { class ProBuilderEditorWindow; class ProBuilderTool; }


namespace Sign {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual void OnAttach() override;
		virtual void OnDettach() override;
		virtual void OnUpdate(Timestep dt) override;
		virtual void OnEvent(Event& event) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

		bool OnWindowResizedEvent(WindowResizedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);

	private:
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<FrameBuffer> m_FrameBuffer;

		Vector2D m_ViewportSize = { 0.0f,0.0f };

		std::shared_ptr<Shader> m_Shader;
		std::vector<std::shared_ptr<Entity>> m_Meshes;
		std::vector<PrimitiveType> m_PendingMeshes;
		int m_InitialEntityCount = 0;
		EditorHistory m_EditorHistory;

		PerspectiveCamera m_EditorCamera;

		// ProBuilder tool & window (basic scaffold)
		std::unique_ptr<ProBuilder::ProBuilderTool> m_ProBuilderTool;
		std::unique_ptr<ProBuilder::ProBuilderEditorWindow> m_ProBuilderWindow;
	};
}


