#pragma once
#include "EditorCommand.h"
#include "Sign/Scene/EntityECS.h"
#include "Sign/Renderer/Entity.h"
#include <vector>


namespace Sign {
	class RemoveObjectCommand : public EditorCommand
	{
	public:
		RemoveObjectCommand(std::vector<EntityECS>& entityList) : m_EntityListECS(&entityList), m_TargetEntity(), m_LegacyList(nullptr), m_LegacyTarget(nullptr) {}
		RemoveObjectCommand(std::vector<std::shared_ptr<Entity>>& legacyList) : m_EntityListECS(nullptr), m_TargetEntity(), m_LegacyList(&legacyList), m_LegacyTarget(nullptr) {}

		void Execute() override;
		void Undo() override;

	private:
		std::vector<EntityECS>* m_EntityListECS = nullptr;
		EntityECS m_TargetEntity;
		std::vector<std::shared_ptr<Entity>>* m_LegacyList = nullptr;
		std::shared_ptr<Entity> m_LegacyTarget;
	};
}

