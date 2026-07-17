#include "signpch.h"
#include "Sign/Renderer/StairsEntity.h"

namespace Sign {
    StairsEntity::StairsEntity()
    {
        if (s_DefaultStairsMesh == nullptr) {
            std::println("[StairsEntity] s_DefaultStairsMesh == nullptr -> creating default stairs mesh");
            s_DefaultStairsMesh = Primitive::Stairs::Create(5, 1.0f, 0.25f, 0.5f, Vector3D(1.0f, 1.0f, 1.0f));
            std::println("[StairsEntity] Created default stairs mesh: verts={}, indices={}", s_DefaultStairsMesh->GetVertexArray()->GetIndexBufferCount() /* rough info */, 0);
        }
        else {
            std::println("[StairsEntity] s_DefaultStairsMesh already created - reusing cached mesh");
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

    }
}