#pragma once
#include "Material.h"



namespace GEngine
{
	namespace Asset
	{
		class Texture;
	}

	using namespace Math;
	class TextureMaterial : public Material
	{
		

	public:
		TextureMaterial(const Asset::Texture& texture, const std::string& vertexFileName = "../GEngine/include/GEngine/Assets/Shaders/texture.vert",
			const std::string& fragFileName =  "../GEngine/include/GEngine/Assets/Shaders/texture.frag");

		void UpdateRenderSettings() override;

	};


}
