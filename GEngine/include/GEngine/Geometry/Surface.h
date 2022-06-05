#pragma once
#include<vector>
#include<Math/Math.h>

namespace GEngine
{
	using namespace Math;

	template<typename SurfaceFunc>
	class Surface
	{
		SurfaceFunc func;

	public:
		Surface(const SurfaceFunc& func): func(func){}

		std::vector<std::vector<Vec3f>> GetPoints(float uStart, float uEnd, int uResolution, float vStart, float vEnd, int vResolution)const
		{
			auto deltaU = (uEnd - uStart) / uResolution;
			auto deltaV = (vEnd - vStart) / vResolution;
			std::vector<std::vector<Vec3f>> points;
			std::vector<Vec3f> vArray;
			float u, v;

			for (auto uIndex = 0; uIndex < uResolution + 1; ++uIndex)
			{
				for (auto vIndex = 0; vIndex < vResolution + 1; ++vIndex)
				{
					u = uStart + uIndex * deltaU;
					v = vStart + vIndex * deltaV;
					vArray.push_back(SurfaceFunc(u, v));
				}

				points.push_back(vArray);
				vArray.clear();
			}

			return points;
		}

		std::vector<std::vector<Vec2f>> GetUVs(int uResolution, int vResolution)const 
		{
			std::vector<std::vector<Vec2f>> UVs;
			std::vector<Vec2f> vArray;

			for (auto uIndex = 0; uIndex < uResolution + 1; ++uIndex)
			{
				for (auto vIndex = 0; vIndex < vResolution + 1; ++vIndex)
				{
					vArray.push_back({ uIndex / uResolution, vIndex / vResolution });
				}

				UVs.push_back(vArray);

				vArray.clear();

			}

			return UVs;
		}

		Vec3f GetNormalAt(float u, float v, float h = 0.0001f)const
		{
			Vec3f uDeriv = (func(u + h, v) - func(u, v)) / h;
			Vec3f vDeriv = (func(u, v + h) - func(u, v)) / h;
			Vec3f normalVector = glm::cross(uDeriv, vDeriv);

			normalVector /= glm::length(normalVector);

			return normalVector;

		}

		std::vector<std::vector<Vec3f>> GetNormals(float uStart, float uEnd, int uResolution, float vStart, float vEnd, int vResolution)const
		{
			auto deltaU = (uEnd - uStart) / uResolution;
			auto deltaV = (vEnd - vStart) / vResolution;
			std::vector<std::vector<Vec3f>>	normals;
			std::vector<Vec3f> vArray;
			float u, v;

			for (auto uIndex = 0; uIndex < uResolution + 1; ++uIndex)
			{
				for (auto vIndex = 0; vIndex < vResolution + 1; ++vIndex)
				{
					u = uStart + uIndex * deltaU;
					v = vStart + vIndex * deltaV;
					vArray.push_back(GetNormalAt(u, v));
				}

				normals.push_back(vArray);
				vArray.clear();
			}

			return normals;
		}
	};
}
