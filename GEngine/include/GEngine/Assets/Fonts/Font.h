#pragma once

struct _TTF_Font;

namespace GEngine::Asset
{
	class Font
	{
	public:
		Font() = default;
		~Font();
		void LoadFont(const std::string& fileName);
		void UnLoad();
		std::unordered_map<int, _TTF_Font*>& GetFontData(){ return m_FontData; }

	private:
		std::unordered_map<int, _TTF_Font*> m_FontData;

	};

}


