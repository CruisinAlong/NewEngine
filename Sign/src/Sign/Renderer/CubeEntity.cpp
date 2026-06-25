#include "CubeEntity.h"

namespace Sign {
	CubeEntity::CubeEntity()
	{
		if (s_DefaultCubeMesh == nullptr) {
			s_DefaultCubeMesh = Primitive::Cube3D::Create({
								{{ 0.0f, 1.0f, 0.0f },
								{ 1.0f, 1.0f, 0.0f },
								{ 1.0f, 0.0f, 0.0f },
								{ 0.0f, 0.0f, 1.0f },
								{ 0.0f, 1.0f, 1.0f },
								{ 1.0f, 1.0f, 1.0f },
								{ 1.0f, 0.0f, 1.0f }
								} });
		}
		SetMesh(s_DefaultCubeMesh);
	}
	void CubeEntity::OnUpdate(Timestep dt)
	{
		Quaternion rotation = m_Rotation;
		rotation.x += 1.0f * dt;
		rotation.y += 1.0f * dt;
		rotation.z += 1.0f * dt;

		Vector3D pos = m_Translation;
		pos.x = std::sin(Time::GetTime() * 0.5) * 10.0f;


		SetRotation(rotation);
		SetTranslation(pos);
	}
}