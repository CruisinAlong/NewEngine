#include "Primitive3D.h"

namespace Sign {
	namespace Primitive {
		std::shared_ptr<Mesh> Cube3D::Create(const std::array<Vector3D, 8>& color)
		{
			VertexPosColor CubeVertices[8];

			for (size_t i = 0; i < 8; i++) {
				CubeVertices[i] = {cubePosition[i], color[i]};
			}


			return std::make_shared<Mesh>(CubeVertices,_countof(CubeVertices),cubeIndices,_countof(cubeIndices));
		}

		std::shared_ptr<Mesh> Sphere::Create(const std::array<Vector3D, 8>& color)
		{
			return std::shared_ptr<Mesh>();
		}
		std::shared_ptr<Mesh> Plane::Create(const std::array<Vector3D, 4>& color)
		{
			VertexPosColor planeVertices[4];

			for (size_t i = 0; i < 4; i++) {
				planeVertices[i] = { planePosition[i], color[i] };
			}
			return std::make_shared<Mesh>(planeVertices, _countof(planeVertices), quadIndices, _countof(quadIndices));
		}
	}
}