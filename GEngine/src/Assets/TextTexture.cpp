#include "gepch.h"
#include "Assets/Textures/TextTexture.h"
#include "Managers/AssetsManager.h"
#include <sdl2/SDL_ttf.h>

namespace GEngine::Asset
{
	using namespace Manager;

	TextTexture::TextTexture(const std::string& text, 
		const std::string& fileName, 
		int pointSize, 
		const Vec3f& color): Texture()
	{
		auto m_Font = AssetsManager::GetFont(fileName);
		// Convert to SDL_Color
		SDL_Color sdlColor{};
		sdlColor.r = static_cast<Uint8>(color.x * 255);
		sdlColor.g = static_cast<Uint8>(color.y * 255);
		sdlColor.b = static_cast<Uint8>(color.z * 255);
		sdlColor.a = 255;

		// Find the font data for this point size
		const auto iter = m_Font->GetFontData().find(pointSize);
		ASSERT(iter != m_Font->GetFontData().end(), std::to_string(pointSize) + " Font size doesn't support");

		TTF_Font* font_ = iter->second;
		TTF_SetFontStyle(font_, TTF_STYLE_BOLD);
		SDL_Surface* surf = TTF_RenderUTF8_Blended(font_, text.c_str(), sdlColor);
		//SDL_Surface* surf = TTF_RenderUTF8_Shaded(font_, text.c_str(), sdlColor, background);

		ASSERT(surf)

		// Convert from surface to texture
		CreateFromSurface(surf);
		SDL_FreeSurface(surf);

	}
}
