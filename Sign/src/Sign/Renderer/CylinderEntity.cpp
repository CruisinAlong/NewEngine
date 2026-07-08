#include "signpch.h"
#include "Sign/Renderer/CylinderEntity.h"

namespace Sign {
    CylinderEntity::CylinderEntity()
    {
        if (s_DefaultCylinderMesh == nullptr) {
            // default radius=1, height=1, segments=32, white color
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
        // no per-frame behavior by default
    }
}
