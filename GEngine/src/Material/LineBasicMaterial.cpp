#include"gepch.h"
#include"Material/LineBasicMaterial.h"

namespace GEngine
{
	void LineBasicMaterial::UpdateRenderSettings()
	{
		glEnable(GL_LINE_SMOOTH);
		glLineWidth(m_RenderSetting.m_PrimitivesSetting.lineSetting.lineWidth);
		switch (m_RenderSetting.m_PrimitivesSetting.lineSetting.lineType)
		{
		case LineType::Connected:
			m_RenderSetting.m_Mode = DrawMode::LINE_STRIP; 
			break;

		case LineType::Loop:
			m_RenderSetting.m_Mode = DrawMode::LINE_LOOP; 
			break;

		case LineType::Segments:
			m_RenderSetting.m_Mode = DrawMode::LINES;
			break;

		}
	}
}