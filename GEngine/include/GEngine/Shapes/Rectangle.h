#pragma once

#include "Geometry/Geometry.h"

namespace GEngine::Shape
{
	class Rectangle : public Geometry
	{
	public:
		Rectangle(float width = 1.0f, float height = 1.0f, const Vec2f& scale = { 1.0f, 1.0f }, const Vec2f& position = { 0.0f, 0.0f }, const Vec2f& alignment = { .5f, .5f }) : Geometry()
		{
			//position
			float x = position.x;
			float y = position.y;

			float a = alignment.x;
			float b = alignment.y;

			float u = scale.x;
			float v = scale.y;



			Vec3f p0 = { x + (-a) * width, y + (-b) * height, 0.f };
			Vec3f p1 = { x + (1 - a) * width, y + (-b) * height, 0.f };
			Vec3f p2 = { x + (-a) * width,  y + (1 - b) * height, 0.f };
			Vec3f p3 = { x + (1 - a) * width,  y + (1 - b) * height, 0.f };

			//color
			Vec3f c0 = { 1.0, 1.0f, 1.0f };
			Vec3f c1 = { 1.0, 0.0f, 0.0f };
			Vec3f c2 = { 0.0, 1.0f, 0.0f };
			Vec3f c3 = { 0.0, 0.0f, 1.0f };

			//texture coords
			Vec2f t0 = { 0.f, 0.f };
			Vec2f t1 = { u, 0.f };
			Vec2f t2 = { 0.f, v };
			Vec2f t3 = { u, v };

			//Normal
			Vec3f n0 = { .0f, .0f, 1.0f };


			Vec3f tangent1, bitangent1;
			Vec3f tangent2, bitangent2;

			Vec3f edge1 = p0 - p2;
			Vec3f edge2 = p1 - p2;
			Vec2f deltaUV1 = t0 - t2;
			Vec2f deltaUV2 = t1 - t2;

			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

			bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);


			edge1 = p1 - p2;
			edge2 = p3 - p2;
			deltaUV1 = t1 - t2;
			deltaUV2 = t3 - t2;

			f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

			bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

			std::vector<Vec3f> positionData = { p0, p1, p2, p2, p1, p3 };
			std::vector<Vec3f> colorData = { c0, c1, c2, c2, c1, c3 };
			std::vector<Vec2f> uvData = { t0, t1, t2, t2, t1, t3 };
			std::vector<Vec3f> normalData = { n0, n0, n0, n0, n0, n0 };
			std::vector<Vec3f> tangentData = { tangent1, tangent1, tangent1, tangent2, tangent2, tangent2 };
			std::vector<Vec3f> bitangentData = { bitangent1, bitangent1, bitangent1, bitangent2, bitangent2, bitangent2 };

			AddAttributes(positionData, colorData, uvData, normalData, tangentData, bitangentData);
			UnBindVAO();
		}
	};
}
