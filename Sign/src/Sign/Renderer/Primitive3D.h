#pragma once
#include <array>
#include <memory>
#include <vector>
#include "Sign/Renderer/Mesh.h"
#include "Sign/Renderer/MeshUtils.h"
#include "Sign/Math/SignMath.h"
namespace Sign {
	namespace Primitive {
		static const std::array<Vector3D, 8> cubePosition = { {
			{-1.0,-1.0,-1.0} , {-1.0,1.0,-1.0 },
			{ 1.0,1.0,-1.0 } , { 1.0,-1.0,-1.0 },
			{ -1.0,-1.0,1.0 }, { -1.0,1.0,1.0 },
			{ 1.0,1.0,1.0 }  , { 1.0,-1.0,1.0 }
		} };
		static const std::array<Vector3D, 4> planePosition = { {
			{-1.0,0.0,1.0 } , 
			{ 1.0,0.0,1.0 } ,
			{ 1.0,0.0,-1.0 }, 
			{ -1.0,0.0,-1.0 }
		} };
		class Cube3D
		{
		public:
			static std::shared_ptr<Mesh> Create(
				const Vector3D& translation = {0.0f,0.0f,0.0f},
				const Vector3D& scale = {1.0f,1.0f,1.0f},
				const Vector3D& rotation = {0.0f, 0.0f, 0.0f},
				const std::array<Vector3D,8>& color = {{
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f}}}
				);
		};

		class Sphere
		{
		public:
			static std::shared_ptr<Mesh> Create(
				const Vector3D& translation = { 0.0f,0.0f,0.0f },
				const Vector3D& scale = { 1.0f,1.0f,1.0f },
				const Vector3D& rotation = { 0.0f, 0.0f, 0.0f},
				const std::array<Vector3D, 8>& color = { {
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f}} }
					);
		};

		class Plane {
		public:
			static std::shared_ptr<Mesh> Create(
				const Vector3D& translation = { 0.0f,0.0f,0.0f },
				const Vector3D& scale = { 10.0f,1.0f,10.0f },
				const Vector3D& rotation = { 0.0f, 0.0f, 0.0f },
				const std::array<Vector3D, 4>& color = { {
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f}} }
					);
		};
	};
}

