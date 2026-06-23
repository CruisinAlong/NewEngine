#pragma once
#include "EditorCommand.h"
#include "Sign/Renderer/Entity.h"
#include "Sign/Renderer/CubeEntity.h"
#include "Sign/Renderer/PlaneEntity.h"
namespace Sign {
	class RemoveObjectCommand : public EditorCommand
	{
	public:
		RemoveObjectCommand(std::vector<std::shared_ptr<Entity>>& entityList) : m_EntityList(entityList),  m_TargetEntity(nullptr){}
		// Inherited via EditorCommand
		void Execute() override;
		void Undo() override;

	private:
		std::vector<std::shared_ptr<Entity>>& m_EntityList;
		std::shared_ptr<Entity> m_TargetEntity;
	};
}

