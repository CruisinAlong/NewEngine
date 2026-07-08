#include "signpch.h"
#include "CreateObjectCommand.h"
#include "Sign/Renderer/CylinderEntity.h"
#include "Sign/Renderer/StairsEntity.h"

namespace Sign {
    void CreateObjectCommand::Execute()
    {
        if (m_Entity == nullptr) {
            switch (m_PType) {
            case PrimitiveType::Cube:
                m_Entity = std::make_shared<CubeEntity>();
                break;
            case PrimitiveType::Plane:
                m_Entity = std::make_shared<PlaneEntity>();
                break;
            case PrimitiveType::Cylinder:
                m_Entity = std::make_shared<CylinderEntity>();
                break;
            case PrimitiveType::Sphere:
                m_Entity = std::make_shared<SphereEntity>();
                break;
            case PrimitiveType::Circle:
                m_Entity = std::make_shared<CircleEntity>();
                break;
            case PrimitiveType::Stairs:
                m_Entity = std::make_shared<StairsEntity>();
                break;
            default:
                std::println("CreateObjectCommand::Execute - unhandled PrimitiveType: {}", static_cast<int>(m_PType));
                break;
            }
        }

        if (!m_Entity) {
            return;
        }

        if (m_UseSpawn) {
            m_Entity->SetTranslation(m_SpawnPos);
        } else {
            std::println("CreateObjectCommand::Execute - No spawn position provided, using default translation.");
        }

        m_EntityList.push_back(m_Entity);
    }

    void CreateObjectCommand::Undo()
    {
        auto it = std::find(m_EntityList.begin(), m_EntityList.end(), m_Entity);
        if (it != m_EntityList.end()) {
            m_EntityList.erase(it);
        }
    }
}