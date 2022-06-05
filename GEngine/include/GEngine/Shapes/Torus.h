#pragma once
#include"ParametricShape.h"

namespace GEngine::Shape
{
	class Torus : public ParametricShape
	{
	public:
		Torus(float centralRadius = 1.f, float tubeRadius = 0.4f, int tubularSegments = 64, int radialSegments = 64, float scale = 1.0f) :
			ParametricShape(0, TwoPi, tubularSegments, 0, TwoPi, radialSegments,
				[&](float u, float v)
				{
					return Vec3f((centralRadius + tubeRadius * glm::cos(v)) * glm::cos(u) * scale,
						(centralRadius + tubeRadius * glm::cos(v)) * glm::sin(u) * scale,
						tubeRadius * glm::sin(v) * scale);
				}){}
	};
}
