#pragma once
#include"Math/Math.h"
#include <string>
#include <Core/UUID.h>
//#include <Assets/Shaders/Shader.h>



using namespace GEngine::Math;
//using namespace GEngine::Asset;

namespace GEngine::Component
{

	struct IDComponent
	{
		UUID ID;
		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
		operator UUID() const{ return ID; }
	};

	struct TransformComponent
	{
		Vec3f Translation{ 0.0f, 0.0f, 0.0f};
		Vec3f Rotation{ 0.0f, 0.0f, 0.0f };
		Vec3f Scale{ 1.0f, 1.0f, 1.0f };


		Mat4 Transform{1.0f};

		TransformComponent() = default;
		TransformComponent(const Mat4& transform): Transform(transform){}
		operator Mat4()const{ return Transform; }
		operator Mat4(){ return Transform; }
		operator Mat4&() { return Transform; }

		
	};


	struct TagComponent
	{
		std::string Name;
		TagComponent() = default;
		TagComponent(const std::string& name): Name(name){}
		operator std::string(){ return Name; }
		operator std::string() const { return Name; }
	};

	struct BasicMaterialComponent
	{
		
		
		//Shader* m_Shader{};
		Vec4f Color{1.0f};
		BasicMaterialComponent() = default;
		BasicMaterialComponent(const Vec4f& color): Color(color) {}
	
	};



	struct CameraComponent
	{

	};

}