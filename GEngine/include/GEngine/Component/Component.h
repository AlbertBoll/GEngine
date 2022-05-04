#pragma once
#include"Math/Math.h"


using namespace GEngine::Math;

namespace GEngine::Component
{
	struct TransformComponent
	{
		Vec3f Translation = { 0.0f, 0.0f, 0.0f };
		Vec3f Rotation = { 0.f, 0.f, 0.f };
		Vec3f Scale = { 1.f, 1.f, 1.f };

		TransformComponent() = default;
		TransformComponent(const Vec3f& translation, const Vec3f& rotation = { 0.f, 0.f, 0.f }, const Vec3f& scale = { 1.f, 1.f, 1.f }) :
			Translation(translation), Rotation(rotation), Scale(scale) {}

		Mat4 GetTransform()
		{
			Mat4 rotation = glm::toMat4(Quat(Rotation));

			return glm::translate(Mat4(1.0f), Translation) * 
						rotation * 
						glm::scale(Mat4(1.0f), Scale);



		}
	};

	struct TagComponent
	{
		std::string Name;
		TagComponent() = default;
		TagComponent(const std::string& name): Name(name){}
	};
}