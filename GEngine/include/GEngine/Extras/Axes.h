#pragma once
#include "Core/Entity.h"

namespace GEngine
{
	class Axes : public Entity
	{
		static Geometry* BuildGeometry(float axis_length = 1.0f);
		
		

		static RefPtr<Material> BuildMaterial(float line_width = 2.0f);

	public:
		Axes(float axis_length = 1.0f, float line_width = 2.0f);
	};

}