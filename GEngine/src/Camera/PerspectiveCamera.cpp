#include "gepch.h"
#include "Camera/PerspectiveCamera.h"
#include "Math/Matrix.h"


namespace GEngine::Camera
{
	void PerspectiveCamera::SetPerspective(float field_of_view, float aspect_ratio, float near_field, float far_field)
	{
		m_Projection = Matrix::MakePerspective(field_of_view, aspect_ratio, near_field, far_field);
		//RecalculateViewProjection();
	}

	void PerspectiveCamera::OnResize(int new_width, int new_height)
	{
		if (!m_IsFixAspectRatio)
		{
			m_CameraSetting.m_PerspectiveSetting.m_AspectRatio = static_cast<float>(new_width) / static_cast<float>(new_height);
			SetPerspective(m_CameraSetting);
		}
		//float near_ = m_CameraSetting.m_PerspectiveSetting.m_Near;
		//float far_ = m_CameraSetting.m_PerspectiveSetting.m_Far;
		//float AspectRatio = m_CameraSetting.m_PerspectiveSetting.m_AspectRatio = static_cast<float>(new_width) / static_cast<float>(new_height);
		//float new_FieldOfView = m_CameraSetting.m_PerspectiveSetting.m_FieldOfView * m_CameraSetting.m_PerspectiveSetting.m_ZoomLevel;
		
		//SetPerspective(new_FieldOfView, AspectRatio, near_, far_);
		
		//GENGINE_CORE_INFO("RESIZE");
	
	}

	void PerspectiveCamera::OnResize(float ratio)
	{
		
		if (!m_IsFixAspectRatio)
		{
			m_CameraSetting.m_PerspectiveSetting.m_AspectRatio = ratio;
			SetPerspective(m_CameraSetting);
		}

		
	}


	void PerspectiveCamera::OnScroll(float new_zoom_level)
	{

		//float delta = new_zoom_level * 0.1f;
		//MouseZoom(delta);
		//OnUpdateView();

		//new_zoom_level = glm::clamp(new_zoom_level, -1.f, 1.f);

		m_CameraSetting.m_PerspectiveSetting.m_FieldOfView = glm::clamp(m_CameraSetting.m_PerspectiveSetting.m_FieldOfView - new_zoom_level, 10.f, 90.f);

		SetPerspective(m_CameraSetting);
	}
	

	void PerspectiveCamera::MouseRotate(const Vec2f& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;

		auto& transform = GetLocalTransformation();
		auto& euler = transform.Rotation;
		auto m_Yaw = ToRadians(euler.y);
		auto m_Pitch = ToRadians(euler.x);
		m_Yaw += yawSign * delta.x * 0.8f;
		m_Pitch += delta.y * 0.8f;

		euler.y = ToDegrees(m_Yaw);
		euler.x = ToDegrees(m_Pitch);
		UpdateLocalTransform();
	}

	void PerspectiveCamera::MousePan(const Vec2f& delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();
		m_FocalPoint += -GetRightDirection() * delta.x * xSpeed * m_Distance;
		m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;
	}
	

	void PerspectiveCamera::MouseZoom(float delta)
	{
		m_Distance -= delta * ZoomSpeed();
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}
	}

	//void PerspectiveCamera::OnUpdateView()
	//{
	//	auto pos = CalculatePosition();
	//	auto orientation = GetOrientation();

	//	m_View = glm::translate(glm::mat4(1.0f), pos) * glm::toMat4(orientation);
	//	m_View = glm::inverse(m_View);
	//}

	Vec3f PerspectiveCamera::CalculatePosition() const
	{
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}

	std::pair<float, float> PerspectiveCamera::PanSpeed() const
	{
		float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float PerspectiveCamera::ZoomSpeed() const
	{
		float distance = m_Distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f); // max speed = 100
		return speed;
	}

}
