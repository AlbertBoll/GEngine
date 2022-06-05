#pragma once
#include "CylindricalShape.h"

namespace GEngine::Shape
{
	class Pyramid : public CylindricalShape
	{
	public:
		Pyramid(float radius = 1.f, float height = 1.f, int sides = 4, int heightSegments = 8, bool bClosed = true)
			: CylindricalShape(0, radius, height, sides, heightSegments, false, bClosed){}
	};
}
