#include "gepch.h"
#include "Geometry/Geometry.h"
#include"Extras/Axes.h"
#include "Material/LineBasicMaterial.h"

namespace GEngine
{
	Geometry* Axes::BuildGeometry(float axis_length)
	{
		auto geometry = new Geometry;

		const std::vector<Vec3f> positionData = { {0.0f, 0.0f, 0.0f}, {axis_length, 0.0f, 0.0f},
												  {0.0f, 0.0f, 0.0f}, {0.0f, axis_length, 0.0f},
												  {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, axis_length} };


		const std::vector<Vec3f> colorData = { {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f, 0.0f},
											   {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f, 0.0f},
											   {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f} };

		geometry->AddAttributes(positionData, colorData);

		return geometry;
	}

	RefPtr<Material> Axes::BuildMaterial(float line_width)
	{
		//auto material = new LineBasicMaterial;
		auto material = CreateRefPtr<LineBasicMaterial>();
		material->SetUniforms<bool>({ {"uUseVertexColor", true} });
		RenderSetting setting;
		
		setting.m_PrimitivesSetting.lineSetting.lineType = LineType::Segments;
		setting.m_PrimitivesSetting.lineSetting.lineWidth = line_width;
		material->SetRenderSettings(setting);
		return material;
	}

	Axes::Axes(float axis_length, float line_width): Entity(BuildGeometry(axis_length), BuildMaterial(line_width))
	{

	}
}
