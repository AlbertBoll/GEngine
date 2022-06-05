#pragma once
#include"Geometry/Geometry.h"
#include"Geometry/Curve.h"

namespace GEngine::Shape
{
	class Tube : public Geometry
	{

	public:
		template<typename Func>
		Tube(const Curve<Func>& curve, float tubeRadius = 0.1f, int radiusSegment = 6) : Geometry()
		{
			auto lengthSegments = curve.m_Divisions;

			auto curvePoints = curve.GetPoints();

			auto frames = curve.GetFrames();

			std::vector<std::vector<Vec3f>> tubePoints;

			std::vector<std::vector<Vec3f>> tubeNormals;

			auto angle = TwoPi / radiusSegment;

			std::vector<Vec3f> radialPoints;
			std::vector<Vec3f> radialNormals;
			Vec3f center;
			Vec3f normal;
			Vec3f point;
			Vec3f N;
			Vec3f B;



			for (auto n = 0; n < lengthSegments; ++n)
			{
				for (auto i = 0; i < radiusSegment; ++i)
				{
					center = curvePoints[n];
					N = frames["normals"][n];
					B = frames["binormals"][n];
					normal = glm::cos(angle * i) * N + glm::sin(angle * i) * B;
					point = center + tubeRadius * normal;

					radialPoints.push_back(point);
					radialNormals.push_back(normal)l
				}

				tubePoints.push_back(radialPoints);

				tubeNormals.push_back(radialNormals);

				radialPoints.clear();
				radialNormals.clear();
			}

			std::vector<Vec3f> vertexPositionData;
			std::vector<Vec3f> vertexColorData;
			std::vector<Vec2f> vertexUVData;
			std::vector<Vec3f> vertexNormalData;

			Vec2f uvA{ 0.f, 0.f };
			Vec2f uvB{ 1.f, 0.f };
			Vec2f uvC{ 1.f, 1.f };
			Vec2f uvD{ 0.f, 1.f };

			Vec3f PA, PB, PC, PD, nA, nB, nC, nD;

			for (auto n = 0; n < lengthSegments - 1; ++n)
			{
				for (auto r = 0; r < radiusSegment; ++r)
				{
					PA = tubePoints[n][r];
					PB = tubePoints[n + 1][r];
					PC = tubePoints[n + 1][r + 1];
					PD = tubePoints[n][r + 1];
					vertexPositionData.insert(vertexPositionData.end(), { PA, PB, PC, PA, PC, PD });
					vertexUVData.insert(vertexUVData.end(), { uvA,uvB,uvC,uvA,uvC,uvD });
					nA = tubeNormals[n + 0][r + 0];
					nB = tubeNormals[n + 1][r + 0];
					nC = tubeNormals[n + 1][r + 1];
					nD = tubeNormals[n + 0][r + 1];
					vertexNormalData.insert(vertexNormalData.end(), { nA,nB,nC, nA,nC,nD });

				}
			}

			AddAttributes(vertexPositionData, vertexColorData, vertexUVData, vertexNormalData);

		}

	};

}
