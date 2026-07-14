#pragma once
#include <vector>
#include "Sign/Scene/ECS/ECSTypes.h"

namespace Sign {
	class EntityManager
	{
	public:
		EntityID CreateEntity();
		void DestroyEntity(EntityID entity);

		void SetSignature(EntityID entity, Signature signature);
		Signature GetSignature(EntityID entity);

		const std::vector<EntityID>& GetAliveEntities() const { return m_AliveEntities; }

	private:
		uint32_t m_NextEntityID = 0;
		std::vector<EntityID> m_AvailableEntities;
		std::vector<Signature> m_Signatures;

		std::vector<EntityID> m_AliveEntities;
		std::unordered_map<EntityID, size_t> m_AliveIndex;
	};

}

