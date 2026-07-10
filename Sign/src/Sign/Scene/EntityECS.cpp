#include "EntityECS.h"

namespace Sign{
    EntityECS::EntityECS(EntityID entity, Scene* scene) : m_EntityHandle(entity), m_Scene(scene)
    {
    }
}
