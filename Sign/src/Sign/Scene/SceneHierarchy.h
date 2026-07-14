#pragma once
#include "Sign/Scene/Scene.h"
#include "Sign/Scene/EntityECS.h"
namespace Sign {
	class SceneHierarchy
	{
	public:
		SceneHierarchy() = default;
		SceneHierarchy(const std::shared_ptr<Scene>& scene);
		~SceneHierarchy();

		void SetContext(const std::shared_ptr<Scene>& scene);

		void OnImGuiRender();
	private:
		std::shared_ptr<Scene> m_Context;
	};
}

