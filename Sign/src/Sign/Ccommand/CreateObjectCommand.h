#pragma once
#include <vector>
#include "Sign/Math/MathUtils.h"
#include "EditorCommand.h"
#include "Sign/Renderer/Entity.h"
#include "Sign/Renderer/CubeEntity.h"
#include "Sign/Renderer/PlaneEntity.h"

namespace Sign {
	class CreateObjectCommand : public EditorCommand
	{
	public:
		CreateObjectCommand(std::vector<std::shared_ptr<Entity>>& entityList, PrimitiveType type) : m_EntityList(entityList), m_PType(type),m_Entity(nullptr) {}
		// Inherited via EditorCommand
		void Execute() override;
		void Undo() override;

	private:
		PrimitiveType m_PType;
		std::vector<std::shared_ptr<Entity>>& m_EntityList;
		std::shared_ptr<Entity> m_Entity;
	};
}

