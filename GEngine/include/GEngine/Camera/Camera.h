#pragma once
#include "Core/Actor.h"

namespace GEngine
{

	enum class CameraType
	{
		Perspective,
		Orthographic
	};

	struct PerspectiveSetting
	{
		float m_ZoomLevel{ 1.0f };
		float m_FieldOfView{ 45.f };
		float m_AspectRatio{ 1.0f };
		float m_Near{ 0.1f };
		float m_Far{ 1000.f };
	};

	struct OrthographicSetting
	{
		float m_Left{ -1.0f };
		float m_Right{ 1.0f };
		float m_Buttom{ -1.0f };
		float m_Top{ 1.0f };
		float m_Near{ -1.0f };
		float m_Far{ 1.0f };

	};
	
	union CameraSetting
	{
		PerspectiveSetting m_PerspectiveSetting;
		OrthographicSetting m_OrthographicSetting;

		CameraSetting(){}


	};



	class CameraBase: public Actor
	{

	public:
		CameraBase() = default;
		CameraBase(const CameraSetting& camera): m_CameraSetting{camera}{}
		void SetCameraSetting(const CameraSetting& camera_setting) { m_CameraSetting = camera_setting; }
		virtual void OnResize(int new_width, int new_height) = 0;
		virtual void OnScroll(float new_zoom_level) = 0;

		void OnUpdateView()
		{
			m_View = glm::inverse(GetWorldTransform());
			RecalculateViewProjection();
		}

		void RecalculateViewProjection() { m_ViewProjection = m_Projection * m_View; }

		Mat4 GetViewProjection() const
		{
			return m_ViewProjection;
		}

		Mat4 GetView() const { return m_View; }

		Mat4 GetProjection() const { return m_Projection; }

		float GetZoomLevel() const { return m_CameraSetting.m_PerspectiveSetting.m_ZoomLevel; }

	private:
		

	protected:
		CameraSetting m_CameraSetting;
		Mat4 m_Projection{ 1.0f };
		Mat4 m_View{ 1.0f };
		Mat4 m_ViewProjection{ 1.0f };
	};
}


