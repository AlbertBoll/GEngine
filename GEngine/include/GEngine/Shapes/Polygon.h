#pragma once
#include <Math/Math.h>
#include "Geometry/Geometry.h"
#include <vector>

namespace GEngine::Shape
{
	using namespace GEngine::Math;

	class Polygon : public Geometry
	{
	public:
		Polygon(int sides = 3, float radius = 1.f) : Geometry()
		{
			const auto segment_angle = TwoPi / sides;

			std::vector<Vec3f> positionData(3 * sides);
			//std::vector<Vec3f> colorData(3 * sides);
			std::vector<Vec3f> colorData;
			std::vector<Vec2f> uvData(3 * sides);

			std::vector<Vec3f> normalData(3 * sides);

			for (int i = 0; i < sides; i++)
			{
				positionData.emplace_back(0.f, 0.f, 0.f);
				positionData.emplace_back(radius * glm::cos(i * segment_angle), radius * glm::sin(i * segment_angle), 0.f);
				positionData.emplace_back(radius * glm::cos((i + 1) * segment_angle), radius * glm::sin((i + 1) * segment_angle), 0.f);
				//colorData.emplace_back(1.f, 1.f, 1.f);
				//colorData.emplace_back(1.f, 0.f, 0.f);
				//colorData.emplace_back(0.f, 0.f, 1.f);
				uvData.emplace_back(0.5f, 0.5f);
				uvData.emplace_back(glm::cos(i * segment_angle) * 0.5f + 0.5f, glm::sin(i * segment_angle) * 0.5f + 0.5f);
				uvData.emplace_back(glm::cos((i + 1) * segment_angle) * 0.5f + 0.5f, glm::sin((i + 1) * segment_angle) * 0.5f + 0.5f);
				normalData.emplace_back(0.f, 0.f, 1.f);
				normalData.emplace_back(0.f, 0.f, 1.f);
				normalData.emplace_back(0.f, 0.f, 1.f);
			}

			AddAttributes(positionData, colorData, uvData, normalData);

		}
	};

}
