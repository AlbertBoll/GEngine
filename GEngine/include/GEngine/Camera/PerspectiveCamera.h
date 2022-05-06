#pragma once
#include "Camera.h"

namespace GEngine::Camera
{
	

	class PerspectiveCamera: public CameraBase
	{
		

	public:
		PerspectiveCamera(float field_of_view = 45.f, float aspect_ratio = 1.0f, float near_field = 0.1f, float far_field = 100.f, float zoom_level = 1.0f) : CameraBase()
		{
			
			SetPerspective(field_of_view, aspect_ratio, near_field, far_field);
			m_CameraSetting.m_PerspectiveSetting.m_ZoomLevel = zoom_level;
			RecalculateViewProjection();
			
		}

		void SetPerspective(float field_of_view = 45.f, float aspect_ratio = 1.0f, float near_field = 0.1f, float far_field = 1000.f);

		

		// Inherited via Camera
		void OnResize(int new_width, int new_height) override;


		// Inherited via CameraBase
		virtual void OnScroll(float new_zoom_level) override;

	};

}

