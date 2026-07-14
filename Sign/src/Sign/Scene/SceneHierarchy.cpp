#include "signpch.h"
#include "SceneHierarchy.h"
#include <imgui.h>

namespace Sign {
	SceneHierarchy::SceneHierarchy(const std::shared_ptr<Scene>& scene)
	{
		SetContext(scene);
	}
	SceneHierarchy::~SceneHierarchy()
	{
	}
	void SceneHierarchy::SetContext(const std::shared_ptr<Scene>& scene)
	{
		m_Context = scene;
	}
	void SceneHierarchy::OnImGuiRender()
	{

		ImGui::Begin("Scene Hierarchy");

		m_Context->m_Registry.each([&](EntityID entityID) {
			EntityECS entity(entityID, m_Context.get());
			auto& tagComp = entity.GetComponent<TagComponent>();
			ImGui::Text("%s", tagComp.Tag.c_str());
			
		});

		ImGui::End();
	}
}