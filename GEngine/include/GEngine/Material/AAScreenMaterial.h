#pragma once
#include "Material.h"

namespace GEngine
{
	class AAScreenMaterial: public Material
	{
	public:
		AAScreenMaterial(unsigned int screenTextureID, const std::string& vertexFileName = "../GEngine/include/GEngine/Assets/Shaders/aa_post.vert",
			             const std::string& fragFileName = "../GEngine/include/GEngine/Assets/Shaders/aa_post.frag");

		void UpdateRenderSettings() override;
	};

}