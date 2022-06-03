#include "gepch.h"
#include "Managers/AssetsManager.h"
#include "Assets/Textures/TextTexture.h"

namespace GEngine::Manager
{
	Texture* AssetsManager::GetTexture(const std::string& texture_file, 
									   const std::string& uniform_name,
									   const std::string& extension, 
									   const TextureInfo& info)
	{
		if (texture_file.empty())
		{
			return nullptr;
		}

		if (auto it = m_TextureMap.find(texture_file); it != m_TextureMap.end())
		{
			return it->second;
		}

		Texture* new_Texture = new(std::nothrow) Texture(texture_file, extension, info);
		ASSERT(new_Texture);

		if (!uniform_name.empty()) new_Texture->SetUniformName(uniform_name);

		m_TextureMap.emplace(texture_file, new_Texture);

		return new_Texture;



	}

	Texture* AssetsManager::GetTextTexture(const std::string& str, 
										   const std::string& font_file, 
										   int pointSize, 
										   const glm::vec3& font_color, 
										   const std::string& uniform_name)
	{
		if (auto it = m_TextureMap.find(font_file); it != m_TextureMap.end())
		{
			return it->second;
		}

		auto* new_texture = new(std::nothrow) TextTexture(str, font_file, pointSize, font_color);
		ASSERT(new_texture);

		if (!uniform_name.empty()) new_texture->SetUniformName(uniform_name);
		m_TextureMap.emplace(font_file, new_texture);

		return new_texture;

	}




	Font* AssetsManager::GetFont(const std::string& font_file)
	{
		if (auto it = m_FontMap.find(font_file); it != m_FontMap.end())
		{
			return  it->second;
		}

		auto* new_font = new(std::nothrow) Font;

		ASSERT(new_font);
		new_font->LoadFont(font_file);

		m_FontMap.emplace(font_file,  new_font);
		return new_font;

	}

	void AssetsManager::FreeTextureResource()
	{
		
		for (auto& ele : m_TextureMap)
		{
			delete ele.second;
		}
		
	}

	void AssetsManager::FreeFontResource()
	{
		for (auto& ele : m_FontMap)
		{
			delete ele.second;
		}
	}

	void AssetsManager::FreeAllResources()
	{
		FreeFontResource();
		FreeTextureResource();
	}
}
