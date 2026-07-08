#pragma once
#include <vector>
#include "Sign/Math/MathUtils.h"
#include "EditorCommand.h"
#include "Sign/Renderer/Entity.h"
#include "Sign/Renderer/CubeEntity.h"
#include "Sign/Renderer/PlaneEntity.h"
#include "Sign/Renderer/SphereEntity.h"
#include "Sign/Renderer/CircleEntity.h"
#include "Sign/Math/SignMath.h" // for Vector3D

// forward declare CylinderEntity to avoid including its header in this header
namespace Sign { class CylinderEntity; }
namespace Sign {
	class CreateObjectCommand : public EditorCommand
	{
	public:
		// existing ctor
		CreateObjectCommand(std::vector<std::shared_ptr<Entity>>& entityList, PrimitiveType type)
			: m_EntityList(entityList), m_PType(type), m_Entity(nullptr), m_UseSpawn(false) {}

		// new ctor: spawn position in world space
		CreateObjectCommand(std::vector<std::shared_ptr<Entity>>& entityList, PrimitiveType type, const Vector3D& spawnPos)
			: m_EntityList(entityList), m_PType(type), m_Entity(nullptr), m_UseSpawn(true), m_SpawnPos(spawnPos) {}

		void Execute() override;
		void Undo() override;

	private:
		PrimitiveType m_PType;
		std::vector<std::shared_ptr<Entity>>& m_EntityList;
		std::shared_ptr<Entity> m_Entity;

		bool m_UseSpawn = false;
		Vector3D m_SpawnPos = {0.0f, 0.0f, 0.0f};
	};
}

