#pragma once
#include "Geometry/Geometry.h"

namespace GEngine::Shape
{
	class Icosahedron : public Geometry
	{
	public:
		Icosahedron(float radius = 1.0f) : Geometry()
		{
			std::vector<Vec3f>positionData;
			std::vector<Vec3f>colorData;
			std::vector<Vec2f>uvData;
			std::vector<Vec3f>vertexNormalData;
			//std::vector<Vec3f>faceNormalData;

			const float t = (1.f + glm::sqrt(5.0f)) / 2.0f;

			std::vector<Vec3f> v
			{
				{-1,  t,  0}, {1, t,  0}, {-1, -t,  0}, {1, -t, 0}, { 0, -1,  t}, { 0, 1, t},
				{ 0, -1, -t}, {0, 1, -t}, { t,  0, -1}, {t,  0, 1}, {-t,  0, -1}, {-t, 0, 1}
			};

			const std::vector<Vec3f> triangleData
			{
				v[0],v[11],v[5], v[0],v[5],v[1],  v[0],v[1],v[7],   v[0],v[7],v[10],  v[0],v[10],v[11],
				v[1],v[5],v[9],  v[5],v[11],v[4], v[11],v[10],v[2], v[10],v[7],v[6],  v[7],v[1],v[8],
				v[3],v[9],v[4],  v[3],v[4],v[2],  v[3],v[2],v[6],   v[3],v[6],v[8],   v[3],v[8],v[9],
				v[4],v[9],v[5],  v[2],v[4],v[11], v[6],v[2],v[10],  v[8],v[6],v[7],   v[9],v[8],v[1]
			};

			for (auto& w : triangleData)
			{
				auto normal = glm::normalize(w);
				float x = normal.x;
				float y = normal.y;
				float z = normal.z;
				float u = atan2(x, z) / TwoPi + 0.5f;
				float v = y * 0.5f + 0.5f;
				auto position = radius * normal;
				positionData.emplace_back(position);
				uvData.emplace_back(u, v);
				vertexNormalData.emplace_back(normal);

			}

			AddAttributes(positionData, colorData, uvData, vertexNormalData);
			UnBindVAO();
		}
	};
}
