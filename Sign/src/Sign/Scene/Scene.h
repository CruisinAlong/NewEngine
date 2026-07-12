#pragma once
#include <string>
#include "Sign/Scene/ECS/Registry.h"
#include "Sign/Scene/ECS/Components.h"
#include "Sign/Renderer/Renderer.h"
namespace Sign {
	class EntityECS;
	class Scene
	{
	public:
		Scene();
		~Scene();

		EntityECS CreateEntity(std::string_view name = std::string());

		void DestroyEntity(EntityECS entity);

		Registry& GetRegistry() { return m_Registry; }
	//Make render Scene private in the FUTURE
	public:
		void RenderScene(EntityID selectedEntity, uint32_t selectedFaceID);
	private:
		Registry m_Registry;
		friend class EntityECS;
	};
}

