#include "gepch.h"
#include "Camera/EditorCamera.h"
#include "Math/Matrix.h"
#include "Core/BaseApp.h"

namespace GEngine::Camera
{
	EditorCamera::EditorCamera(float fov, float aspect_ratio, float near_field, float far_field): CameraBase()
	{
		m_CameraSetting.m_PerspectiveSetting.m_Far = far_field;
		m_CameraSetting.m_PerspectiveSetting.m_Near = near_field;
		m_CameraSetting.m_PerspectiveSetting.m_FieldOfView = fov;
		m_CameraSetting.m_PerspectiveSetting.m_AspectRatio = aspect_ratio;
	
		SetPerspective(fov, aspect_ratio, near_field, far_field);
	}

	void EditorCamera::SetPerspective(float field_of_view, float aspect_ratio, float near_field, float far_field)
	{
		m_Projection = Matrix::MakePerspective(field_of_view, aspect_ratio, near_field, far_field);
	}

	void EditorCamera::SetPerspective(const CameraSetting& setting)
	{
		SetPerspective(setting.m_PerspectiveSetting.m_FieldOfView,
			setting.m_PerspectiveSetting.m_AspectRatio,
			setting.m_PerspectiveSetting.m_Near,
			setting.m_PerspectiveSetting.m_Far);
	}

	void EditorCamera::Update(Timestep ts)
	{
		using namespace GEngine;
		auto input = BaseApp::GetInputManager();
		auto& keyboardState = input->GetKeyboardState();
		auto& mouseState = input->GetMouseState();
		if(keyboardState.IsKeyPressed(GENGINE_KEY_LCTRL))
		//if (Input::IsKeyPressed(Key::LeftAlt))
		{
			const Vec2f mouse = { mouseState.GetPosition().x, mouseState.GetPosition().y };
			Vec2f delta = (mouse - m_InitialMousePosition) * 0.003f;
			m_InitialMousePosition = mouse;

			if (mouseState.isButtonPressed(GENGINE_BUTTON_MIDDLE))
				MousePan(delta);
			else if (mouseState.isButtonPressed(GENGINE_BUTTON_LEFT))
				MouseRotate(delta);
			else if (mouseState.isButtonPressed(GENGINE_BUTTON_RIGHT))
				MouseZoom(delta.y);
		}

		OnUpdateView();
	}

	void EditorCamera::OnUpdateView()
	{
		auto pos = GetPosition();
		auto orientation = GetOrientation();

		m_View = glm::translate(glm::mat4(1.0f), pos) * glm::toMat4(orientation);
		m_View = glm::inverse(m_View);

	}

	void EditorCamera::OnResize(int new_width, int new_height)
	{
		m_ViewportWidth = (float)new_width;
		m_ViewportHeight = (float)new_height;

		if (!m_IsFixAspectRatio)
		{
			m_CameraSetting.m_PerspectiveSetting.m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
			SetPerspective(m_CameraSetting);
		}
	}

	void EditorCamera::OnResize(float ratio)
	{
		if (!m_IsFixAspectRatio)
		{
			m_CameraSetting.m_PerspectiveSetting.m_AspectRatio = ratio;
			SetPerspective(m_CameraSetting);
		}

	}


	void EditorCamera::OnScroll(float new_zoom_level)
	{
		float delta = new_zoom_level * 0.1f;
		MouseZoom(delta);
		OnUpdateView();
	}

	Vec3f EditorCamera::CalculatePosition() const
	{
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}

	void EditorCamera::MousePan(const Vec2f& delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();
		m_FocalPoint += -GetRightDirection() * delta.x * xSpeed * m_Distance;
		m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;
	}

	void EditorCamera::MouseRotate(const Vec2f& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;

		auto& transform = GetLocalTransformation();
		auto& euler = transform.Rotation;
		auto m_Yaw = ToRadians(euler.y);
		auto m_Pitch = ToRadians(euler.x);
		m_Yaw += yawSign * delta.x * RotationSpeed();
		m_Pitch += delta.y * RotationSpeed();

		euler.y = ToDegrees(m_Yaw);
		euler.x = ToDegrees(m_Pitch);
	}

	void EditorCamera::MouseZoom(float delta)
	{
		m_Distance -= delta * ZoomSpeed();
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}
	}

	std::pair<float, float> EditorCamera::PanSpeed() const
	{
		float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float EditorCamera::RotationSpeed() const
	{
		return 0.8f;
	}

	float EditorCamera::ZoomSpeed() const
	{
		float distance = m_Distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f); // max speed = 100
		return speed;
	}
}
