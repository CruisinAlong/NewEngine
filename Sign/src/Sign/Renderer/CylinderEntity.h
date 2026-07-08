#pragma once

#include "Sign/Renderer/Entity.h"
#include "Sign/Renderer/Primitive3D.h"

namespace Sign {
    class CylinderEntity : public Entity
    {
    public:
        CylinderEntity();
        ~CylinderEntity();

        // Inherited via Entity
        void OnUpdate(Timestep dt) override;
    private:
        inline static std::shared_ptr<Mesh> s_DefaultCylinderMesh = nullptr;
    };
}
