#pragma once
#include "EditorCommand.h"
#include "Sign/Renderer/Entity.h"
#include "Sign/Renderer/CubeEntity.h"
#include "Sign/Renderer/PlaneEntity.h"

namespace Sign {
	class DeleteAllCommand : public EditorCommand
	{
	public:
		DeleteAllCommand(std::vector<std::shared_ptr<Entity>>& entityList, int initialCount) : m_EntityList(entityList), m_ProtectedCount(initialCount) {}
		// Inherited via EditorCommand
		void Execute() override;
		void Undo() override;

	private:
		std::vector<std::shared_ptr<Entity>>& m_EntityList;
		std::vector<std::shared_ptr<Entity>> m_CachedBackUp;

		int m_ProtectedCount;
	};
}

