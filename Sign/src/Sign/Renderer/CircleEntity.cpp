#include "CircleEntity.h"

namespace Sign {
	CircleEntity::CircleEntity()
	{
		SetMesh(Primitive::Circle::Create(Vector3D(1.0f,1.0f,2.0f), Vector3D(2.0f,0.0f,1.0f)));
	}
}
