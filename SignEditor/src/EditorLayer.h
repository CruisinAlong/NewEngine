#pragma once
#include <Sign.h>
// Forward declare probuilder types to avoid coupling headers here
namespace ProBuilder { class ProBuilderEditorWindow; class ProBuilderTool; }
class EditorLayer : public Sign::Layer
{
public:
	EditorLayer();
	virtual void OnAttach() override;
	virtual void OnDettach() override;
	virtual void OnUpdate(Sign::Timestep dt) override;
	virtual void OnEvent(Sign::Event& event) override;
	virtual void OnRender() override;
	virtual void OnImGuiRender() override;

	bool OnWindowResizedEvent(Sign::WindowResizedEvent& e);
	bool OnKeyPressedEvent(Sign::KeyPressedEvent& e);

private:
	std::shared_ptr<Sign::VertexArray> m_VertexArray;
	std::shared_ptr<Sign::FrameBuffer> m_FrameBuffer;

	Sign::Vector2D m_ViewportSize = { 0.0f,0.0f };

	std::shared_ptr<Sign::Shader> m_Shader;
	std::vector<std::shared_ptr<Sign::Entity>> m_Meshes;
	std::vector<Sign::PrimitiveType> m_PendingMeshes;
	int m_InitialEntityCount = 0;
	Sign::EditorHistory m_EditorHistory;

	Sign::PerspectiveCamera m_EditorCamera;

	// ProBuilder tool & window (basic scaffold)
	std::unique_ptr<ProBuilder::ProBuilderTool> m_ProBuilderTool;
	std::unique_ptr<ProBuilder::ProBuilderEditorWindow> m_ProBuilderWindow;
};

