#pragma once
#include"Polygon.h"

namespace GEngine::Shape
{
	class Hexagon : public Polygon
	{
	public:
		Hexagon(float radius = 1.0f): Polygon(6, radius){}
	};
}
