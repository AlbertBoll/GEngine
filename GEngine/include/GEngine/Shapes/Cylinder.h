#pragma once
#include"CylindricalShape.h"

namespace GEngine::Shape
{
	class Cylinder : public CylindricalShape
	{
	public:
		Cylinder(float radiusTop = 1.f, float radiusBottom = 1.f, float height = 1.f, int radialSegments = 32, int heightSegments = 4, bool bTopClosed = true, bool bBottomClosed = true) : 
			CylindricalShape(radiusTop, radiusBottom, height, radialSegments, heightSegments, bTopClosed, bBottomClosed){}
	};
}
