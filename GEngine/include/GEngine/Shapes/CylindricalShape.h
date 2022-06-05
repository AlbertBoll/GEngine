#pragma once
#include"ParametricShape.h"
#include"Polygon.h"
#include"Math/Matrix.h"

namespace GEngine::Shape
{


	class CylindricalShape : public ParametricShape
	{
		
	public:
		CylindricalShape(float radiusTop = 1.f, float radiusBottom = 1.f, float height = 1.f, int radialSegments = 32, int heightSegments = 4, bool bTopClosed = false, bool bBottomClosed = false):
			ParametricShape(0.f, TwoPi, radialSegments, 0.f, 1.f, heightSegments,
				[&](float u, float v)
				{
					return Vec3f((v * radiusTop + (1 - v) * radiusBottom) * glm::sin(u),
						height * (v - 0.5f),
						(v * radiusTop + (1 - v) * radiusBottom) * glm::cos(u));
				})
		{
			Geometry* geo = nullptr;

			if (bTopClosed)
			{
				geo = new Polygon(radialSegments, radiusTop);
				const Mat4 transform = Matrix::MakeTranslation(0.f, height / 2.0f, 0.0f) * Matrix::MakeRotationY(-3.1415f / 2.0f) * Matrix::MakeRotationX(-3.1415f / 2.0f);
				geo->ApplyTransform(transform);
				Merge(geo);
				delete geo;
				geo = nullptr;

			}

			if (bBottomClosed)
			{
				geo = new Polygon(radialSegments, radiusBottom);
				const Mat4 transform = Matrix::MakeTranslation(0.f, -height / 2.0f, 0.0f) * Matrix::MakeRotationY(-3.1415f / 2.0f) * Matrix::MakeRotationX(3.1415f / 2.0f);
				geo->ApplyTransform(transform);
				Merge(geo);
				delete geo;
				geo = nullptr;
			}
		
		}

	};
}
