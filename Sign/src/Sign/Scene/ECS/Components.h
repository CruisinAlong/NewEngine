#pragma once
#include <string>
#include "Sign/Scene/ECS/ECSTypes.h"
#include "Sign/Scene/ECS/SparseSet.h"
#include "Sign/Math/SignMath.h"
#include "Sign/Renderer/Mesh.h"
#include "Sign/Shader/Shader.h"
namespace Sign {

	inline ComponentType GetNextComponentTypeID() {
		static ComponentType nextID = 0;
		return nextID++;
	}

	template<typename T>
	ComponentType GetComponentTypeID() {
		static ComponentType typeID = GetNextComponentTypeID();
		return typeID++;
	}
	struct TransformComponent {
		Vector3D Translation = { 0.0f,0.0f,0.0f };
		Quaternion Rotation = { 0.0f,0.0f,0.0f,0.0f };
		Vector3D Scale = { 1.0f,1.0f,1.0f };
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Vector3D& translation) : Translation(translation) {}

		Mat4 GetTransform() const {
			return	Mat4::scale(Scale)
				* Mat4::rotateX(Rotation.x)
				* Mat4::rotateY(Rotation.y)
				* Mat4::rotateZ(Rotation.z)
				* Mat4::translate(Translation);
		}


		EntityID m_entity = INVALID_ENTITY_ID;
	};
	
	struct MeshRendererComponent {
		std::shared_ptr<Mesh> Mesh;
		std::shared_ptr<Shader> Shader;
		MeshRendererComponent() = default;
		MeshRendererComponent(const MeshRendererComponent&) = default;
		MeshRendererComponent(const std::shared_ptr<Sign::Mesh>& mesh, const std::shared_ptr<Sign::Shader>& shader = Sign::Shader::GetDefault()) : Mesh(mesh), Shader(shader) {}
		EntityID m_entity = INVALID_ENTITY_ID;
	};

	struct TagComponent {
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(std::string_view tag) : Tag(tag) {}
		EntityID m_entity = INVALID_ENTITY_ID;
	};



}