#include "signpch.h"
#include "Sign/Renderer/StairsEntity.h"

namespace Sign {
    StairsEntity::StairsEntity()
    {
        if (s_DefaultStairsMesh == nullptr) {
            // default steps=5, width=1, stepHeight=0.25, depthPerStep=0.5, white color
            s_DefaultStairsMesh = Primitive::Stairs::Create(5, 1.0f, 0.25f, 0.5f, Vector3D(1.0f, 1.0f, 1.0f));
        }
        SetMesh(s_DefaultStairsMesh);
    }

    StairsEntity::~StairsEntity()
    {
        s_DefaultStairsMesh.reset();
        s_DefaultStairsMesh = nullptr;
    }

    void StairsEntity::OnUpdate(Timestep dt)
    {
        // no per-frame behavior by default
    }
}
