#include "Primitive3D.h"

namespace Sign {
    namespace Primitive {
        std::shared_ptr<Mesh> Stairs::Create(int steps, float stepWidth, float stepHeight, float depthPerStep, const Vector3D& Color)
        {
            std::vector<VertexPosColor> vertices;
            std::vector<WORD> indices;

            for (int s = 0; s < steps; s++) {
                float y0 = s * stepHeight;
                float y1 = (s + 1) * stepHeight;
                float z0 = -s * depthPerStep;
                float z1 = -(s * depthPerStep + depthPerStep);
                float x0 = -stepWidth * 0.5f;
                float x1 = stepWidth * 0.5f;

                VertexPosColor v0{ {x0, y0, z0}, Color };
                VertexPosColor v1{ {x0, y1, z0}, Color };
                VertexPosColor v2{ {x1, y1, z0}, Color };
                VertexPosColor v3{ {x1, y0, z0}, Color };
                VertexPosColor v4{ {x0, y0, z1}, Color };
                VertexPosColor v5{ {x0, y1, z1}, Color };
                VertexPosColor v6{ {x1, y1, z1}, Color };
                VertexPosColor v7{ {x1, y0, z1}, Color };

                WORD baseIndex = (WORD)vertices.size();
                vertices.push_back(v0);
                vertices.push_back(v1);
                vertices.push_back(v2);
                vertices.push_back(v3);
                vertices.push_back(v4);
                vertices.push_back(v5);
                vertices.push_back(v6);
                vertices.push_back(v7);

                for (int i = 0; i < 36; i++) {
                    indices.push_back((WORD)(baseIndex + cubeIndices[i]));
                }
            }

            return std::make_shared<Mesh>(vertices.data(), (uint32_t)vertices.size(), indices.data(), (uint32_t)indices.size());
        }
    }
}
