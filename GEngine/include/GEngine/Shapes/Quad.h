#pragma once
#include"Geometry/Geometry.h"

namespace GEngine::Shape
{
	class Quad : public Geometry
	{
	public:
		Quad() : Geometry()
		{
			Vec2f p0{ -1.f, -1.f };
			Vec2f p1{ 1.f, -1.f };
			Vec2f p2{ -1.f,  1.f };
			Vec2f p3{ 1.f,  1.f };

			Vec2f t0{ 0.f, 0.f };
			Vec2f t1{ 1.f, 0.f };
			Vec2f t2{ 0.f,  1.f };
			Vec2f t3{ 1.f,  1.f };

			std::vector<Vec2f> positionData{ p0, p1, p3, p0, p3, p2 };
			std::vector<Vec3f> colorData;
			std::vector<Vec2f> uvData{ t0, t1, t3, t0, t3, t2 };

			AddAttributes(positionData, colorData, uvData);
			UnBindVAO();
		}
	};
}
