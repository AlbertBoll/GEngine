#pragma once
#include "Camera.h"

namespace GEngine::Camera
{
	class PerspectiveCamera :public CameraBase
	{
		

	public:
		PerspectiveCamera(float field_of_view = 45.f, float aspect_ratio = 1.0f, float near_field = 0.1f, float far_field = 100.f, float zoom_level = 1.0f) : CameraBase()
		{
			CameraSetting setting;
			setting.m_PerspectiveSetting.m_Far = far_field;
			setting.m_PerspectiveSetting.m_Near = near_field;
			setting.m_PerspectiveSetting.m_FieldOfView = field_of_view;
			setting.m_PerspectiveSetting.m_AspectRatio = aspect_ratio;
			setting.m_PerspectiveSetting.m_ZoomLevel = zoom_level;

			SetCameraSetting(setting);
			SetPerspective(field_of_view, aspect_ratio, near_field, far_field);
			
		}

		void SetPerspective(float field_of_view = 45.f, float aspect_ratio = 1.0f, float near_field = 0.1f, float far_field = 100.f);

		

		// Inherited via Camera
		void OnResize(int new_width, int new_height) override;

	};

}

