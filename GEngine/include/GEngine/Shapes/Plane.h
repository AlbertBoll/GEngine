#pragma once
#include"ParametricSurface.h"

namespace GEngine::Shape
{
	class Plane : public ParametricSurface
	{
	public:
		Plane(float width = 1.f, float height = 1.f, int width_res = 8, int height_res = 8) :
			ParametricSurface(-width / 2.f, width / 2.f, width_res, -height / 2.f, height / 2.f, height_res,
				[](float u, float v){return Vec3f{ u, v, 0.0f }; }) {}
	};
}