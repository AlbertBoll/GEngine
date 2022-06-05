#pragma once
#include"CylindricalShape.h"

namespace GEngine::Shape
{
	class Prism : public CylindricalShape
	{
	public:
		Prism(float radius = 1.f, float height = 1.f, int sides = 4, int heightSegments = 4, bool bClosed = true) :
			CylindricalShape(radius, radius, height, sides, heightSegments, bClosed, bClosed)
		{}
	};
}
