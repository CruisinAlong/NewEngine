#include "EntityManager.h"

namespace Sign {
    EntityID EntityManager::CreateEntity()
    {
        if (!m_AvailableEntites.empty()) {
            EntityID id = m_AvailableEntites.back();
            m_AvailableEntites.pop_back();
            return id;
        }


        return m_NextEntityID++;
    }

    void EntityManager::DestroyEntity(EntityID entity)
    {
        m_AvailableEntites.push_back(entity);
    }
    void EntityManager::SetSignature(EntityID entity, Signature signature)
    {
        if (entity >= m_Signatures.size())
            m_Signatures.resize(entity + 1);
        m_Signatures[entity] = signature;
    }
    Signature EntityManager::GetSignature(EntityID entity)
    {
        if (entity >= m_Signatures.size())
            return{};
        return m_Signatures[entity];
    }
}
