#include "signpch.h"
#include "Sign/Renderer/CylinderEntity.h"

namespace Sign {
    CylinderEntity::CylinderEntity()
    {
        if (s_DefaultCylinderMesh == nullptr) {
            s_DefaultCylinderMesh = Primitive::Cylinder::Create(1.0f, 1.0f, 32, Vector3D(1.0f, 1.0f, 1.0f));
        }
        SetMesh(s_DefaultCylinderMesh);
    }

    CylinderEntity::~CylinderEntity()
    {
        s_DefaultCylinderMesh.reset();
        s_DefaultCylinderMesh = nullptr;
    }

    void CylinderEntity::OnUpdate(Timestep dt)
    {
    }
}
