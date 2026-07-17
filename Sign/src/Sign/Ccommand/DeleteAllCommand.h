#pragma once
#include "EditorCommand.h"
#include "Sign/Scene/EntityECS.h"
#include "Sign/Renderer/Entity.h"
#include <vector>

namespace Sign {
	class DeleteAllCommand : public EditorCommand
	{
	public:
		// ECS constructor
		DeleteAllCommand(std::vector<EntityECS>& entityList, int initialCount) : m_EntityListECS(&entityList), m_ProtectedCount(initialCount), m_LegacyList(nullptr) {}
		// Legacy constructor
		DeleteAllCommand(std::vector<std::shared_ptr<Entity>>& legacyList, int initialCount) : m_EntityListECS(nullptr), m_ProtectedCount(initialCount), m_LegacyList(&legacyList) {}

		// Inherited via EditorCommand
		void Execute() override;
		void Undo() override;

	private:
		// ECS mode
		std::vector<EntityECS>* m_EntityListECS = nullptr;
		std::vector<EntityECS> m_CachedBackUp;

		// legacy mode
		std::vector<std::shared_ptr<Entity>>* m_LegacyList = nullptr;
		std::vector<std::shared_ptr<Entity>> m_CachedLegacyBackUp;

		int m_ProtectedCount;
	};
}

