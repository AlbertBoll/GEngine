#pragma once
#include"Math/Math.h"


using namespace GEngine::Math;

namespace GEngine::Component
{
	struct TransformComponent
	{
	
		Mat4 Transform{1.0f};

		TransformComponent() = default;

	
	};


	struct TagComponent
	{
		std::string Name;
		TagComponent() = default;
		TagComponent(const std::string& name): Name(name){}
	};


	struct CameraComponent
	{

	};

}