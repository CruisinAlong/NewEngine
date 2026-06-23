#include "PlaneEntity.h"

namespace Sign {
	PlaneEntity::PlaneEntity()
	{
		SetMesh(Primitive::Plane::Create());
		SetScale(Vector3D(10.f, 1.f, 10.0f));
	}
}