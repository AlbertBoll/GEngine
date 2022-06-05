#pragma once
#include"Geometry/Geometry.h"

namespace GEngine::Shape
{
	class Points : public Geometry
	{
	public:
		Points(const std::vector<Vec3f>& vertexData) : Geometry()
		{
			AddAttributes(vertexData);
		}
	};
}
