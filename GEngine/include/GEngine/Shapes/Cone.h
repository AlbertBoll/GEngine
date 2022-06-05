#pragma once
#include"CylindricalShape.h"

namespace GEngine::Shape
{
	class Cone : public CylindricalShape
	{
	public:
	public:
		Cone(float radius = 1.f, float height = 1.f, int radialSegments = 32, int heightSegments = 4, bool bClosed = true) :
			CylindricalShape(0, radius, height, radialSegments, heightSegments, false, bClosed)
		{}
	};
}
