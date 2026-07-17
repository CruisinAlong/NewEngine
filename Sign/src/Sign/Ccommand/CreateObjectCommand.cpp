#include "signpch.h"
#include "CreateObjectCommand.h"
#include <algorithm>
#include "Sign/Renderer/Primitive2D.h"
#include "Sign/Math/MathUtils.h"
#include "Sign/Renderer/CubeEntity.h"
#include "Sign/Renderer/PlaneEntity.h"
#include "Sign/Renderer/SphereEntity.h"
#include "Sign/Renderer/CircleEntity.h"

namespace Sign {

void CreateObjectCommand::Execute()
{
    if (m_EntityListECS && m_Scene) {
        // ECS path
        if (!m_Entity && m_Scene) {
            m_Entity = m_Scene->CreateEntity();

            switch (m_PType) {
            case PrimitiveType::Cube:
                m_Entity.AddComponent<MeshRendererComponent>(Primitive::Cube3D::Create());
                break;
            case PrimitiveType::Plane:
                m_Entity.AddComponent<MeshRendererComponent>(Primitive::Plane::Create());
                break;
            case PrimitiveType::Sphere:
                m_Entity.AddComponent<MeshRendererComponent>(Primitive::Sphere::Create());
                break;
            case PrimitiveType::Circle:
                m_Entity.AddComponent<MeshRendererComponent>(Sign::Primitive::Circle::Create());
                break;
            default:
                m_Entity.AddComponent<MeshRendererComponent>(Primitive::Cube3D::Create());
                break;
            }

            auto& t = m_Entity.GetComponent<TransformComponent>();
            t.Translation = { MathUtils::Random_Float(-10.0f, 10.0f), MathUtils::Random_Float(-10.0f, 10.0f), MathUtils::Random_Float(-10.0f, 10.0f) };
        }

        if (m_Entity) {
            m_EntityListECS->push_back(m_Entity);
        }

        return;
    }

    // legacy path
    if (m_EntityListLegacy) {
        if (!m_LegacyEntity) {
            // create legacy OOP entity for backward compatibility
            switch (m_PType) {
            case PrimitiveType::Cube:
                m_LegacyEntity = std::make_shared<CubeEntity>();
                break;
            case PrimitiveType::Plane:
                m_LegacyEntity = std::make_shared<PlaneEntity>();
                break;
            case PrimitiveType::Sphere:
                m_LegacyEntity = std::make_shared<SphereEntity>();
                break;
            case PrimitiveType::Circle:
                m_LegacyEntity = std::make_shared<CircleEntity>();
                break;
            default:
                m_LegacyEntity = std::make_shared<CubeEntity>();
                break;
            }
        }

        if (m_LegacyEntity) {
            m_EntityListLegacy->push_back(m_LegacyEntity);
        }
    }
}

void CreateObjectCommand::Undo()
{
    if (m_EntityListECS) {
        if (!m_EntityListECS->empty()) {
            auto it = std::find(m_EntityListECS->begin(), m_EntityListECS->end(), m_Entity);
            if (it != m_EntityListECS->end())
                m_EntityListECS->erase(it);
        }

        if (m_Scene && m_Entity) {
            m_Scene->DestroyEntity(m_Entity);
            m_Entity = EntityECS();
        }

        return;
    }

    if (m_EntityListLegacy) {
        if (!m_EntityListLegacy->empty()) {
            auto it = std::find(m_EntityListLegacy->begin(), m_EntityListLegacy->end(), m_LegacyEntity);
            if (it != m_EntityListLegacy->end())
                m_EntityListLegacy->erase(it);
        }
        m_LegacyEntity.reset();
    }
}

}