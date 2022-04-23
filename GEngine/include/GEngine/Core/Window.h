#pragma once
#include "Utility.h"
#include "string"

namespace GEngine
{

	//enum GraphicContext
	//{
	//	OPENGL,
	//	VULKAN,
	//	DIRECTX
	//};

	enum class WindowFlags: uint8_t
	{
		INVISIBLE = 0x1,
		FULLSCREEN = 0X2,
		BORDERLESS = 0x4,
		RESIZABLE = 0x8
	};

	struct WindowProperties
	{
		std::string m_Title = "GEngine Editor App";
		unsigned int m_Width = 800;
		unsigned int m_Height = 600;
		unsigned int m_MinWidth = 480;
		unsigned int m_MinHeight = 320;
		float m_Red = 0.f;
		float m_Green = 0.f;
		float m_Blue = 0.f;
		BitFlags<WindowFlags, uint8_t>flag{ WindowFlags::RESIZABLE };
		bool m_IsVsync = true;
	};

	class Window
	{
	public:
		unsigned int GetScreenWidth()const { return m_ScreenWidth; }
		unsigned int GetScreenHeight()const { return m_ScreenWidth; }
		virtual void Initialize(const WindowProperties& winProp) = 0;
		virtual void SwapBuffer()const = 0;
		virtual void ShutDown() = 0;
		virtual void SetTitle(const std::string& title) const = 0;


	protected:
		//SDL_Window* m_Window{};
		unsigned int m_ScreenWidth, m_ScreenHeight;

	};

}