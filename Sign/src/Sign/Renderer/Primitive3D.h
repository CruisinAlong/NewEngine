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
			{-0.5,-0.5,-0.5} , {-0.5,0.5,-0.5 },
			{ 0.5,0.5,-0.5 } , { 0.5,-0.5,-0.5 },
			{ -0.5,-0.5,0.5 }, { -0.5,0.5,0.5 },
			{ 0.5,0.5,0.5 }  , { 0.5,-0.5,0.5 }
		} };
		static const std::array<Vector3D, 4> planePosition = { {
			{-0.5,0.0,0.5 } ,
			{ 0.5,0.0,0.5 } ,
			{ 0.5,0.0,-0.5 },
			{ -0.5,0.0,-0.5 }
		} };
		struct Cube3D
		{
		public:
			static std::shared_ptr<Mesh> Create(
				const std::array<Vector3D,6>& color = {{
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f}}}
				);
		};

		struct Cylinder
		{
		public:
			static std::shared_ptr<Mesh> Create(float radius = 1.0f, float height = 1.0f, int segments = 32, const Vector3D& color = Vector3D(1.0f, 1.0f, 1.0f));
		};

		struct Stairs
		{
		public:
			static std::shared_ptr<Mesh> Create(int steps = 5, float stepWidth = 1.0f, float stepHeight = 0.25f, float depthPerStep = 0.5f, const Vector3D& color = Vector3D(1.0f, 1.0f, 1.0f));
		};

		struct Sphere
		{
		public:
			static std::shared_ptr<Mesh> Create(
				const Vector3D& centerColor = Vector3D(1.0f, 1.0f, 1.0f));

		private:
			static void AddIndices(std::vector<WORD>& indices, int i1, int i2, int i3);
			static void Interpolate(const float* v1, const float* v2, float t, float radius, float* out);
		};

		struct Plane {
		public:
			static std::shared_ptr<Mesh> Create(
				const std::array<Vector3D, 4>& color = { {
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},
					{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f}} }
					);
		};
	};
}

