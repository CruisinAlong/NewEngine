#include "signpch.h"
#include "Primitive3D.h"
#include <cstdio>
#include <cmath>

namespace Sign {
	namespace Primitive {

		void Sphere::AddIndices(std::vector<WORD>& indices, int i1, int i2, int i3)
		{
			indices.push_back((WORD)i1);
			indices.push_back((WORD)i2);
			indices.push_back((WORD)i3);
		}

		void Sphere::Interpolate(const float* v1, const float* v2, float t, float radius, float* out)
		{
			float x = v1[0] + (v2[0] - v1[0]) * t;
			float y = v1[1] + (v2[1] - v1[1]) * t;
			float z = v1[2] + (v2[2] - v1[2]) * t;
			float len = std::sqrtf(x * x + y * y + z * z);
			if (len <= 1e-6f) len = 1.0f;
			float inv = radius / len;
			out[0] = x * inv;
			out[1] = y * inv;
			out[2] = z * inv;
		}

		std::shared_ptr<Mesh> Cube3D::Create(const std::array<Vector3D, 6>& color)
		{
			std::vector<VertexPosColor> finalVertices;
			std::vector<WORD> indices;

			const int triCount = _countof(cubeIndices) / 3;
			finalVertices.reserve(triCount * 3);
			indices.reserve(triCount * 3);

			for (int t = 0; t < triCount; ++t) {
				uint32_t faceID = (uint32_t)(t / 2);
				for (int j = 0; j < 3; ++j) {
					WORD src = cubeIndices[t * 3 + j];
					VertexPosColor v;
					v.Position = cubePosition[src];
					v.Color = color[faceID % 6];
					v.FaceID = faceID;
					finalVertices.push_back(v);
					indices.push_back((WORD)(finalVertices.size() - 1));
				}
			}

			return std::make_shared<Mesh>(finalVertices.data(), (uint32_t)finalVertices.size(), indices.data(), (uint32_t)indices.size());
		}

		std::shared_ptr<Mesh> Cylinder::Create(float radius, float height, int segments, const Vector3D& Color)
		{
			if (segments < 3) segments = 3;
			std::vector<float> rawVerts;
			std::vector<WORD> srcIndices;

			float half = height * 0.5f;

			// Top center
			rawVerts.push_back(0.0f); rawVerts.push_back(half); rawVerts.push_back(0.0f);

			// Top ring
			for (int i = 0; i < segments; i++) {
				float angle = (MathUtils::PI * 2.0f * i) / (float)segments;
				float x = radius * std::cosf(angle);
				float z = radius * std::sinf(angle);
				rawVerts.push_back(x); rawVerts.push_back(half); rawVerts.push_back(z);
			}

			// Bottom ring
			for (int i = 0; i < segments; i++) {
				float angle = (MathUtils::PI * 2.0f * i) / (float)segments;
				float x = radius * std::cosf(angle);
				float z = radius * std::sinf(angle);
				rawVerts.push_back(x); rawVerts.push_back(-half); rawVerts.push_back(z);
			}

			// Bottom center
			rawVerts.push_back(0.0f); rawVerts.push_back(-half); rawVerts.push_back(0.0f);

			const WORD topCenterIndex = 0;
			const WORD topStart = 1;
			const WORD bottomStart = (WORD)(1 + segments);
			const WORD bottomCenterIndex = (WORD)(rawVerts.size() / 3 - 1);

			// Top fan
			for (int i = 0; i < segments; i++) {
				srcIndices.push_back(topCenterIndex);
				srcIndices.push_back((WORD)(topStart + i));
				srcIndices.push_back((WORD)(topStart + ((i + 1) % segments)));
			}

			// Side quads (two triangles each)
			for (int i = 0; i < segments; i++) {
				int next = (i + 1) % segments;
				// triangle 1
				srcIndices.push_back((WORD)(topStart + i));
				srcIndices.push_back((WORD)(bottomStart + i));
				srcIndices.push_back((WORD)(topStart + next));
				// triangle 2
				srcIndices.push_back((WORD)(topStart + next));
				srcIndices.push_back((WORD)(bottomStart + i));
				srcIndices.push_back((WORD)(bottomStart + next));
			}

			// Bottom fan
			for (int i = 0; i < segments; i++) {
				srcIndices.push_back(bottomCenterIndex);
				srcIndices.push_back((WORD)(bottomStart + ((i + 1) % segments)));
				srcIndices.push_back((WORD)(bottomStart + i));
			}

			std::vector<VertexPosColor> finalVertices;
			std::vector<WORD> finalIndices;
			finalVertices.reserve(srcIndices.size());
			finalIndices.reserve(srcIndices.size());

			int triTotal = (int)srcIndices.size() / 3;
			for (int t = 0; t < triTotal; ++t) {
				uint32_t faceID;
				if (t < segments) {
					faceID = (uint32_t)t; 
				}
				else if (t < segments + 2 * segments) {
					int sideTriIndex = t - segments; 
					int segmentIndex = sideTriIndex / 2; 
					faceID = (uint32_t)segments + (uint32_t)segmentIndex; 
				}
				else {
					int bottomTriIndex = t - (segments + 2 * segments); 
					faceID = (uint32_t)segments + (uint32_t)segments + (uint32_t)bottomTriIndex; 
				}

				for (int j = 0; j < 3; ++j) {
					WORD vIdx = srcIndices[t * 3 + j];
					VertexPosColor v;
					v.Position = {
						rawVerts[vIdx * 3 + 0],
						rawVerts[vIdx * 3 + 1],
						rawVerts[vIdx * 3 + 2]
					};
					v.Color = Color;
					v.FaceID = faceID;
					finalVertices.push_back(v);
					finalIndices.push_back((WORD)(finalVertices.size() - 1));
				}
			}

			return std::make_shared<Mesh>(finalVertices.data(), (uint32_t)finalVertices.size(), finalIndices.data(), (uint32_t)finalIndices.size());
		}

		std::shared_ptr<Mesh> Sphere::Create(const Vector3D& Color)
		{
			return ResourceCache::GetOrCreate<Mesh>("DefaultSphere", [&]()->std::shared_ptr<Mesh> {
				const float H_ANGLE = MathUtils::ConvertToRadians(72.0f);
				const float V_ANGLE = std::atanf(1.0f / 2.0f);
				float radius = 1.0f;

				std::vector<float> vertices;
				std::vector<WORD> indices;
				float z, xy;
				float hAngle1 = -MathUtils::PI / 2 - H_ANGLE / 2;
				float hAngle2 = -MathUtils::PI / 2;

				vertices.insert(vertices.end(), { 0.0f,0.0f,radius });

				for (int i = 0; i < 5; i++) {
					z = radius * std::sin(V_ANGLE);
					xy = radius * std::cos(V_ANGLE);

					vertices.push_back(xy * std::cos(hAngle1));
					vertices.push_back(xy * std::sin(hAngle1));
					vertices.push_back(z);

					hAngle1 += H_ANGLE;
				}
				for (int i = 0; i < 5; i++) {
					z = radius * std::sin(V_ANGLE);
					xy = radius * std::cos(V_ANGLE);
					vertices.push_back(xy * std::cos(hAngle2));
					vertices.push_back(xy * std::sin(hAngle2));
					vertices.push_back(-z);
					hAngle2 += H_ANGLE;
				}

				vertices.insert(vertices.end(), { 0.0f,0.0f,-radius });

				for (int i = 1; i <= 5; i++) {
					int next = i % 5 + 1;
					int bot = i + 5;
					int botNext = next + 5;
					AddIndices(indices, 0, i, next); // Top
					AddIndices(indices, i, bot, next); // Upper Middle
					AddIndices(indices, bot, botNext, next); // Lower Middle
					AddIndices(indices, 11, botNext, bot); // Bot
				}

				const int SUBDIVISION = 3;
				for (int s = 0; s < SUBDIVISION; s++) {
					std::vector<float> tmpVertices = vertices;
					std::vector<WORD> tmpIndices = indices;
					vertices.clear();
					indices.clear();
					WORD index = 0;
					for (int i = 0; i < (int)tmpIndices.size(); i += 3)
					{
						const float* v1 = &tmpVertices[tmpIndices[i] * 3];
						const float* v2 = &tmpVertices[tmpIndices[i + 1] * 3];
						const float* v3 = &tmpVertices[tmpIndices[i + 2] * 3];

						std::vector<float> newVs;
						newVs.insert(newVs.end(), v1, v1 + 3);

						for (int j = 1; j <= SUBDIVISION; j++)
						{
							float a = (float)j / SUBDIVISION;
							float newV1[3], newV2[3], newV3[3];
							Interpolate(v1, v2, a, radius, newV1);
							Interpolate(v1, v3, a, radius, newV2);

							newVs.insert(newVs.end(), newV1, newV1 + 3);
							for (int k = 1; k < j; k++)
							{
								float b = (float)k / j;
								Interpolate(newV1, newV2, b, radius, newV3);
								newVs.insert(newVs.end(), newV3, newV3 + 3);
							}
							newVs.insert(newVs.end(), newV2, newV2 + 3);
						}

						for (int j = 1; j <= SUBDIVISION; j++)
						{
							for (int k = 0; k < j; k++)
							{
								WORD i1 = (j - 1) * j / 2 + k;
								WORD i2 = j * (j + 1) / 2 + k;

								const float* sv1 = &newVs[i1 * 3];
								const float* sv2 = &newVs[i2 * 3];
								const float* sv3 = &newVs[(i2 + 1) * 3];
								vertices.insert(vertices.end(), sv1, sv1 + 3);
								vertices.insert(vertices.end(), sv2, sv2 + 3);
								vertices.insert(vertices.end(), sv3, sv3 + 3);
								AddIndices(indices, index, index + 1, index + 2);
								index += 3;

								if (k < j - 1)
								{
									WORD i2b = i1 + 1;
									const float* sv2b = &newVs[i2b * 3];
									vertices.insert(vertices.end(), sv1, sv1 + 3);
									vertices.insert(vertices.end(), sv3, sv3 + 3);
									vertices.insert(vertices.end(), sv2b, sv2b + 3);
									AddIndices(indices, index, index + 1, index + 2);
									index += 3;
								}
							}
						}
					}
				}

				std::vector<VertexPosColor> finalVertices;
				for (int i = 0; i < (int)vertices.size(); i += 3) {
					VertexPosColor v;
					v.Position = { vertices[i],vertices[i + 2], vertices[i + 1] };
					v.Color = Color;
					finalVertices.push_back(v);
				}

				std::vector<VertexPosColor> finalVerts;
				std::vector<WORD> finalIdx;
				finalVerts.reserve(indices.size());
				finalIdx.reserve(indices.size());

				int triCount = (int)indices.size() / 3;
				for (int t = 0; t < triCount; ++t) {
					uint32_t faceID = (uint32_t)t;
					for (int j = 0; j < 3; ++j) {
						WORD src = indices[t * 3 + j];
						VertexPosColor v;
						v.Position = { vertices[src * 3 + 0], vertices[src * 3 + 1], vertices[src * 3 + 2] };
						v.Color = Color;
						v.FaceID = faceID;
						finalVerts.push_back(v);
						finalIdx.push_back((WORD)(finalVerts.size() - 1));
					}
				}

				return std::make_shared<Mesh>(finalVerts.data(), (uint32_t)finalVerts.size(), finalIdx.data(), (uint32_t)finalIdx.size());
				});
		}

		std::shared_ptr<Mesh> Stairs::Create(int steps, float stepWidth, float totalHeight, float totalDepth, const Vector3D& Color)
		{
			if (steps < 1) steps = 1;

			float stepHeight = totalHeight / (float)steps;
			float depthPerStep = totalDepth / (float)steps;

			std::vector<VertexPosColor> finalVertices;
			std::vector<WORD> finalIndices;

			float halfW = stepWidth * 0.5f;

			static const WORD cubeIndices8[36] = {
				0,1,2, 0,2,3,
				4,7,6, 4,6,5,
				1,5,6, 1,6,2,
				0,3,7, 0,7,4,
				0,4,5, 0,5,1,
				3,2,6, 3,6,7
			};

			for (int s = 0; s < steps; ++s)
			{
				float frontZ = -s * depthPerStep;
				float backZ = -(s + 1) * depthPerStep;
				float height = (s + 1) * stepHeight;

				VertexPosColor box[8] = {
					{ Vector3D(-halfW, 0.0f,  frontZ), Color, 0 },
					{ Vector3D(-halfW, height, frontZ), Color, 0 },
					{ Vector3D(halfW, height, frontZ), Color, 0 },
					{ Vector3D(halfW, 0.0f,  frontZ), Color, 0 },
					{ Vector3D(-halfW, 0.0f,  backZ), Color, 0 },
					{ Vector3D(-halfW, height, backZ), Color, 0 },
					{ Vector3D(halfW, height, backZ), Color, 0 },
					{ Vector3D(halfW, 0.0f,  backZ), Color, 0 }
				};

				const int triCount = 12; 
				for (int t = 0; t < triCount; ++t) {
					uint32_t faceID = (uint32_t)(s * 6 + (t / 2)); 
					for (int j = 0; j < 3; ++j) {
						WORD src = cubeIndices8[t * 3 + j];
						VertexPosColor v;
						v.Position = box[src].Position;
						v.Color = box[src].Color;
						v.FaceID = faceID;
						finalVertices.push_back(v);
						finalIndices.push_back((WORD)(finalVertices.size() - 1));
					}
				}
			}

			return std::make_shared<Mesh>(finalVertices.data(), (uint32_t)finalVertices.size(), finalIndices.data(), (uint32_t)finalIndices.size());
		}

		std::shared_ptr<Mesh> Plane::Create(const std::array<Vector3D, 4>& color)
		{
			return ResourceCache::GetOrCreate<Mesh>("DefaultPlane", [&]()->std::shared_ptr<Mesh> {
				VertexPosColor planeVertices[4];

				for (size_t i = 0; i < 4; i++) {
					planeVertices[i] = { planePosition[i], color[i],0 };
				}
				return std::make_shared<Mesh>(planeVertices, _countof(planeVertices), quadIndices, _countof(quadIndices));
				});
		}
	}
}