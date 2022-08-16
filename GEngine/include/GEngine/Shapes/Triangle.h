#pragma once
#include"Polygon.h"

namespace GEngine::Shape
{
	class Triangle : public Polygon
	{
	public:
		Triangle(float radius = 1.0f) : Polygon(3, radius) {}
	};
}
