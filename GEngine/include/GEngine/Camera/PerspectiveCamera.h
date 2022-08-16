#pragma once
#include "Camera.h"

namespace GEngine::Camera
{
	

	class PerspectiveCamera: public CameraBase
	{
		

	public:
		PerspectiveCamera(float field_of_view = 45.f, float aspect_ratio = 1.0f, float near_field = 0.01f, float far_field = 1000.f, float zoom_level = 1.0f) : CameraBase()
		{
			m_CameraSetting.m_PerspectiveSetting.m_Far = far_field;
			m_CameraSetting.m_PerspectiveSetting.m_Near = near_field;
			m_CameraSetting.m_PerspectiveSetting.m_FieldOfView = field_of_view;
			m_CameraSetting.m_PerspectiveSetting.m_AspectRatio = aspect_ratio;
			//m_CameraSetting.m_PerspectiveSetting.m_ZoomLevel = zoom_level;
			SetPerspective(field_of_view, aspect_ratio, near_field, far_field);
			
		}

		void SetPerspective(float field_of_view = 45.f, float aspect_ratio = 1.0f, float near_field = 0.01f, float far_field = 1000.f);

		void SetPerspective(const CameraSetting& setting)
		{
			SetPerspective(setting.m_PerspectiveSetting.m_FieldOfView,
							setting.m_PerspectiveSetting.m_AspectRatio,
							  setting.m_PerspectiveSetting.m_Near,
							  setting.m_PerspectiveSetting.m_Far);
		}

		void SetFar(float _far)
		{
			m_CameraSetting.m_PerspectiveSetting.m_Far = _far;
			SetPerspective(m_CameraSetting);

		}

		void SetNear(float _near)
		{
			m_CameraSetting.m_PerspectiveSetting.m_Near = _near;
			SetPerspective(m_CameraSetting);
		}

		void SetFieldOfView(float field_of_view)
		{
			//m_CameraSetting.m_PerspectiveSetting.m_FieldOfView = field_of_view;
			SetPerspective(m_CameraSetting);
		}

		void SetAspectRatio(float aspect_ratio)
		{
			m_CameraSetting.m_PerspectiveSetting.m_AspectRatio = aspect_ratio;
			SetPerspective(m_CameraSetting);
		}


		// Inherited via Camera
		void OnResize(int new_width, int new_height) override;

		void OnResize(float ratio) override;

	

		// Inherited via CameraBase
		virtual void OnScroll(float new_zoom_level) override;

		void MouseRotate(const Vec2f& delta)override;
		void MousePan(const Vec2f& delta) override;
		void MouseZoom(float delta);
		//void OnUpdateView()override;

	private:
		Vec3f CalculatePosition() const;
		std::pair<float, float> PanSpeed() const;
		float ZoomSpeed() const;

	private:
		Vec3f m_FocalPoint = { 0.0f, 0.0f, 0.0f };
		Vec2f m_InitialMousePosition = { 0.0f, 0.0f };
		float m_Distance = 10.0f;

	};

	using PerspectiveCamera = Camera::PerspectiveCamera;

}

