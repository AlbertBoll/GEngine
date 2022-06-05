#pragma once
#include"Geometry/Geometry.h"

namespace GEngine::Shape
{
	class Line : public Geometry
	{
	public:
		Line(const std::vector<Vec3f>& vertexPositionData) : Geometry()
		{
			size_t vertexCount = vertexPositionData.size();
			float totalArcLength = 0.f;
			std::vector<float> vertexArcLengthData{ 0.f };
			vertexArcLengthData.reserve(vertexCount - 1);
			float segmentLength;
			for (auto i = 1; i < vertexCount; i++)
			{
				segmentLength = glm::length(vertexPositionData[i] - vertexPositionData[i - 1]);
				totalArcLength += segmentLength;
				vertexArcLengthData.push_back(totalArcLength);
			}

			AddAttributes(vertexPositionData, vertexArcLengthData);
			

		}
	};
}
