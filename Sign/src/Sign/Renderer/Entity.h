#pragma once

#include <memory>
#include <string>
#include "Sign/Math/SignMath.h"
#include "Sign/Renderer/Mesh.h"

namespace Sign {
	enum class PrimitiveType {
		Cube,
		Plane,
		Circle
	};
	class Entity
	{
	public:
		Entity(const std::string& name = "Entity");
		virtual ~Entity() = default;
		const Mat4& GetTransform();
		const Vector3D& GetTranslation() const { return m_Translation; }
		const Vector3D& GetScale() const { return m_Scale; }
		const Quaternion& GetRotation() const { return m_Rotation; }
		const std::string GetName() const { return m_EntityName; }
		const std::shared_ptr<Mesh>& GetMesh() const{ return m_Mesh; }

		void SetTranslation(const Vector3D& pos) { m_Translation = pos; RecalculateTransform(); }
		void SetScale(const Vector3D& scale) { m_Scale = scale; RecalculateTransform(); };
		void SetRotation(const Quaternion& rotation) { m_Rotation = rotation; RecalculateTransform(); }
		void SetMesh(const std::shared_ptr<Mesh>& mesh) { m_Mesh = mesh; }

	private:
		void RecalculateTransform();
	protected:
		std::string m_EntityName;

		Vector3D m_Translation;
		Vector3D m_Scale;
		Quaternion m_Rotation;
		Mat4 m_Transform;

		bool m_Dirty = true;

		std::shared_ptr<Mesh> m_Mesh = nullptr;
	};
}

