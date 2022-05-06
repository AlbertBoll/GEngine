#include "gepch.h"
#include "Camera/PerspectiveCamera.h"
#include "Math/Matrix.h"


namespace GEngine::Camera
{
	void PerspectiveCamera::SetPerspective(float field_of_view, float aspect_ratio, float near_field, float far_field)
	{
		m_Projection = Matrix::MakePerspective(field_of_view, aspect_ratio, near_field, far_field);
	}

	void PerspectiveCamera::OnResize(int new_width, int new_height)
	{
		float AspectRatio = m_CameraSetting.m_PerspectiveSetting.m_AspectRatio = static_cast<float>(new_width) / static_cast<float>(new_height);
		float new_FieldOfView = m_CameraSetting.m_PerspectiveSetting.m_FieldOfView * m_CameraSetting.m_PerspectiveSetting.m_ZoomLevel;

		SetPerspective(new_FieldOfView, AspectRatio, 0.1f, 1000.f);
	}

}
