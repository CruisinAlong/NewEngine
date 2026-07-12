#include "Registry.h"

namespace Sign{
	void Registry::DestroyEntity(EntityID entity)
	{
		for (auto& [type, pool] : m_Pools) {
			pool->Remove(entity);

		}

		m_EntityManager.DestroyEntity(entity);
	}

	Signature Registry::GetSignature(EntityID entity)
	{
		return m_EntityManager.GetSignature(entity);
	}
}

