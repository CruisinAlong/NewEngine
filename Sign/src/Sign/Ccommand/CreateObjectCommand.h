// Reworked to use ECS entities
#pragma once
#include "EditorCommand.h"
#include "Sign/Scene/EntityECS.h"
#include "Sign/Scene/Scene.h"
#include "Sign/Renderer/Primitive3D.h"
#include "Sign/Scene/ECS/Components.h"
#include "Sign/Renderer/Entity.h" // for PrimitiveType and legacy Entity
#include <vector>

namespace Sign {
	class CreateObjectCommand : public EditorCommand {
	public:
		// ECS constructor
		CreateObjectCommand(std::vector<EntityECS>& entityList, Scene* scene, PrimitiveType type)
			: m_EntityListECS(&entityList), m_EntityListLegacy(nullptr), m_Scene(scene), m_PType(type) {}

		// legacy constructor (keeps old behavior)
		CreateObjectCommand(std::vector<std::shared_ptr<Entity>>& legacyList, PrimitiveType type)
			: m_EntityListECS(nullptr), m_EntityListLegacy(&legacyList), m_Scene(nullptr), m_PType(type) {}

		void Execute() override;
		void Undo() override;

	private:
		PrimitiveType m_PType;
		// ECS mode
		std::vector<EntityECS>* m_EntityListECS = nullptr;
		Scene* m_Scene = nullptr;
		EntityECS m_Entity;
		// legacy mode
		std::vector<std::shared_ptr<Entity>>* m_EntityListLegacy = nullptr;
		std::shared_ptr<Entity> m_LegacyEntity;
	};
}

