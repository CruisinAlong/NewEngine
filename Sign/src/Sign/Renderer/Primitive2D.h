#pragma once
#include <array>
#include <memory>
#include <vector>
#include "Sign/Renderer/Mesh.h"
#include "Sign/Renderer/MeshUtils.h"
#include "Sign/Math/SignMath.h"
namespace Sign {
	namespace Primitive {
		static const std::array<Vector3D, 8> trianglePosition = { {
			{-1.0,-1.0,-1.0} , {-1.0,1.0,-1.0 },
			{ 1.0,1.0,-1.0 } , { 1.0,-1.0,-1.0 },
			{ -1.0,-1.0,1.0 }, { -1.0,1.0,1.0 },
			{ 1.0,1.0,1.0 }  , { 1.0,-1.0,1.0 }
		} };

		struct Triangle
		{
		public:
			static std::shared_ptr<Mesh> Create(
				const std::array<Vector3D, 8>& color = { {
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f}} }
					);
		};

		struct Circle
		{
		public:
			static std::shared_ptr<Mesh> Create(
				const Vector3D& centerColor, const Vector3D& outerColor);
		};
	};
}

