#include "signpch.h"
#include "TriangleEntity.h"

namespace Sign {
	TriangleEntity::TriangleEntity()
	{
		if (s_DefaultTriangleMesh == nullptr) {
			s_DefaultTriangleMesh = Primitive::Triangle::Create();
		}
		SetMesh(s_DefaultTriangleMesh);
	}
	void TriangleEntity::OnUpdate(Timestep dt)
	{
	}
}