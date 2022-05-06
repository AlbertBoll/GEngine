#include "gepch.h"
#include "Camera/PerspectiveCamera.h"
#include "Math/Matrix.h"


namespace GEngine::Camera
{
	void PerspectiveCamera::SetPerspective(float field_of_view, float aspect_ratio, float near_field, float far_field)
	{

		m_CameraSetting.m_PerspectiveSetting.m_Far = far_field;
		m_CameraSetting.m_PerspectiveSetting.m_Near = near_field;
		m_CameraSetting.m_PerspectiveSetting.m_FieldOfView = field_of_view;
		m_CameraSetting.m_PerspectiveSetting.m_AspectRatio = aspect_ratio;
		//m_CameraSetting.m_PerspectiveSetting.m_ZoomLevel = zoom_level;
		m_Projection = Matrix::MakePerspective(field_of_view, aspect_ratio, near_field, far_field);
		RecalculateViewProjection();
	}

	void PerspectiveCamera::OnResize(int new_width, int new_height)
	{

		float near_ = m_CameraSetting.m_PerspectiveSetting.m_Near;
		float far_ = m_CameraSetting.m_PerspectiveSetting.m_Far;
		float AspectRatio = m_CameraSetting.m_PerspectiveSetting.m_AspectRatio = static_cast<float>(new_width) / static_cast<float>(new_height);
		float new_FieldOfView = m_CameraSetting.m_PerspectiveSetting.m_FieldOfView * m_CameraSetting.m_PerspectiveSetting.m_ZoomLevel;

		SetPerspective(new_FieldOfView, AspectRatio, near_, far_);
	
	}

	void PerspectiveCamera::OnScroll(float new_zoom_level)
	{

		float near_ = m_CameraSetting.m_PerspectiveSetting.m_Near;
		float far_ = m_CameraSetting.m_PerspectiveSetting.m_Far;
		m_CameraSetting.m_PerspectiveSetting.m_ZoomLevel = new_zoom_level;
		//const float m_FieldOfView_ = glm::clamp(m_FieldOfView * m_ZoomLevel, 15.f, 90.f);
		const float m_FieldOfView = m_CameraSetting.m_PerspectiveSetting.m_FieldOfView * m_CameraSetting.m_PerspectiveSetting.m_ZoomLevel;
		//const float m_Aspect_ = m_AspectRatio * m_ZoomLevel;

		SetPerspective(m_FieldOfView, m_CameraSetting.m_PerspectiveSetting.m_AspectRatio, near_, far_);
		
	}

}
