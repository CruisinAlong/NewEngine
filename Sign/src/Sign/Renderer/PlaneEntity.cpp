#include "PlaneEntity.h"

namespace Sign {
	PlaneEntity::PlaneEntity()
	{
		if (s_DefaultPlaneMesh == nullptr) {
			s_DefaultPlaneMesh = Primitive::Plane::Create();
		}
		SetMesh(s_DefaultPlaneMesh);
		SetScale(Vector3D(10.f, 1.f, 10.0f));
	}
	void PlaneEntity::OnUpdate(Timestep dt)
	{

	}
}