#include "CubeEntity.h"

namespace Sign {
	CubeEntity::CubeEntity()
	{
		SetMesh(Primitive::Cube3D::Create({
		{{ 0.0f, 1.0f, 0.0f },
		{ 1.0f, 1.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f }
		} }));
	}
}