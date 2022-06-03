#include "gepch.h"
#include "Assets/Fonts/Font.h"
#include <sdl2/SDL_ttf.h>

namespace GEngine::Asset
{
	Font::~Font()
	{
		UnLoad();
	}

	void Font::LoadFont(const std::string& fileName)
	{
		// We support these font sizes
		std::vector<int> fontSizes = {
			8, 9,
			10, 11, 12, 14, 16, 18,
			20, 22, 24, 26, 28,
			30, 32, 34, 36, 38,
			40, 42, 44, 46, 48,
			52, 56,
			60, 64, 68,
			72
		};


		for (auto& size : fontSizes)
		{

			TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);

			ASSERT(font, "Failed to load font " + fileName + " in size " + std::to_string(size))

				m_FontData.emplace(size, font);
		}

	}

	void Font::UnLoad()
	{
		for (auto& font : m_FontData)
		{
			TTF_CloseFont(font.second);
		}
	}

}