#pragma once
#include "Camera.h"

namespace GEngine::Camera
{
	class OrthographicCamera : public CameraBase
	{

	public:
		OrthographicCamera(float left = -1.f, float right = 1.f, float bottom = -1.f,
			float top = 1.f, float near_ = -1.f, float far_ = 1.f);

		void SetOrthographic(float left = -1.f, float right = 1.f, float bottom = -1.f,
			float top = 1.f, float near_ = -1.f, float far_ = 1.f);

		void OnResize(int new_width, int new_height) override;

		void OnResize(float ratio) override;

		void OnScroll(float new_zoom_level)override{}
	};
}


