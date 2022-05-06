#include "gepch.h"
#include "Camera/OrthographicCamera.h"
#include "Math/Matrix.h"

namespace GEngine::Camera
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near_, float far_): CameraBase()
	{
		
		SetOrthographic(left, right, bottom, top, near_, far_);
	}

	void OrthographicCamera::SetOrthographic(float left, float right, float bottom, float top, float Near, float Far)
	{
		m_CameraSetting.m_OrthographicSetting.m_Left = left;
		m_CameraSetting.m_OrthographicSetting.m_Right = right;
		m_CameraSetting.m_OrthographicSetting.m_Buttom = bottom;
		m_CameraSetting.m_OrthographicSetting.m_Top = top;
		m_CameraSetting.m_OrthographicSetting.m_Near = Near;
		m_CameraSetting.m_OrthographicSetting.m_Far = Far;
		
		m_Projection = Matrix::MakeOrthographic(left, right, bottom, top, Near, Far);
		RecalculateViewProjection();
	
	}

	void OrthographicCamera::OnResize(int new_width, int new_height)
	{


		float aspectRatio = static_cast<float>(new_width) / static_cast<float>(new_height);
		float near_ = m_CameraSetting.m_OrthographicSetting.m_Near;
		float far_ = m_CameraSetting.m_OrthographicSetting.m_Far;
		SetOrthographic(-aspectRatio, aspectRatio, -aspectRatio, aspectRatio, near_, far_);
	
	}


}
