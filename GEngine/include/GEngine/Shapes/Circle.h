#pragma once
#include "Polygon.h"

namespace GEngine::Shape
{
	class Circle : public Polygon
	{
	public:
		Circle(float radius = 1.0f, int segments = 32): Polygon(segments, radius){}
	};
}
