#pragma once
#include "Camera/Camera.h"

namespace GEngine::Camera
{
	class EditorCamera : public CameraBase
	{
	public:
		EditorCamera(float fov = 45.f, float aspect_ratio = 1.0f, float near_field = 0.01f, float far_field = 1000.f);
		void SetPerspective(float field_of_view = 45.f, float aspect_ratio = 1.0f, float near_field = 0.01f, float far_field = 1000.f);
		void SetPerspective(const CameraSetting& setting);

		void Update(Timestep ts)override;
		void OnUpdateView()override;
		void OnResize(int new_width, int new_height) override;
		void OnResize(float ratio) override;
		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }


		//float GetPitch() const { return GetLocalTransformation().; }
		//float GetYaw() const { return m_Yaw; }

		// Inherited via CameraBase
		virtual void OnScroll(float new_zoom_level) override;


	private:

		Vec3f CalculatePosition() const;
		void MousePan(const Vec2f& delta)override;
		void MouseRotate(const Vec2f& delta)override;
		void MouseZoom(float delta);

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;

	private:
		//float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;
		//Mat4 m_ViewMatrix;
		//Vec3f m_Position = { 0.0f, 0.0f, 0.0f };
		Vec3f m_FocalPoint = { 0.0f, 0.0f, 0.0f };

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		float m_Distance = 10.0f;
		//float m_Pitch = 0.0f, m_Yaw = 0.0f;

		//float m_ViewportWidth = 1280, m_ViewportHeight = 720;

	};
}


