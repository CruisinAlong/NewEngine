#pragma once
#include "Sign/Layer.h"
#include <print>
#include "Sign/Input.h"
#include "Sign/Events/Event.h"
#include "Sign/Events/KeyEvents.h"
#include "Sign/Events/MouseEvents.h"
#include "Sign/Renderer/Renderer.h"
#include "Sign/Shader/Shader.h"
#include "Sign/Buffers/VertexBuffer.h"
#include "Sign/Buffers/IndexBuffer.h"
#include "Sign/Buffers/VertexArray.h"
#include "Sign/Renderer/Mesh.h"
#include "Sign/Renderer/Pipeline.h"

class AppLayer : public Sign::Layer
{
public:
	AppLayer();
	virtual void OnAttach() override;
	virtual void OnUpdate(float ts) override;
	virtual void OnEvent(Sign::Event& event) override;
	virtual void OnRender() override;

private:
	std::shared_ptr<Sign::VertexArray> m_VertexArray;
	std::unique_ptr<Sign::GraphicsPipeline> m_GraphicsPipeline;
	std::shared_ptr<Sign::Shader> m_Shader;
};

