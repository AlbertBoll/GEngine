#pragma once
#include "Utility.h"
#include <string>

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

	enum class WindowPos: uint8_t
	{
		TopLeft,
		TopRight,
		ButtomLeft,
		ButtomRight,
		Center

	};

	//struct ScreenParams
	//{
	//	int m_DisplayWidth = 2560;
	//	int m_DisplayHeight = 1440;
	//};

	struct WindowProperties
	{
		std::string m_Title = "GEngine Editor App";
		uint32_t m_Width = 800;
		uint32_t m_Height = 600;
		uint32_t m_MinWidth = 480;
		uint32_t m_MinHeight = 320;
		float m_Red = 0.f;
		float m_Green = 0.f;
		float m_Blue = 0.f;
		BitFlags<WindowFlags, uint8_t>flag{ WindowFlags::RESIZABLE };
		WindowPos m_WinPos = WindowPos::Center;
		int m_XPaddingToCenterY = 20;
		int m_YPaddingToCenterX = 20;
		bool m_IsVsync = true;

		void SetColor(float R, float G, float B) { m_Red = R; m_Green = G; m_Blue = B; }
		void SetCornFlowerBlue() {
			m_Red = static_cast<float>(0x64)/ static_cast<float>(0xFF); 
			m_Green = static_cast<float>(0x95)/ static_cast<float>(0xFF);
			m_Blue = static_cast<float>(0xED)/ static_cast<float>(0xFF);
		}
	};

	//abstract base class of window
	class Window
	{
	public:

		virtual ~Window(){};
		uint32_t GetScreenWidth()const { return m_ScreenWidth; }
		uint32_t GetScreenHeight()const { return m_ScreenWidth; }
		virtual void Initialize(const WindowProperties& winProp = {}) = 0;
		virtual void SwapBuffer()const = 0;
		virtual void ShutDown() = 0;
		virtual void SetTitle(const std::string& title) const = 0;
		virtual std::string GetTitle() const = 0;
		virtual uint32_t GetWindowID()const = 0;
		virtual void BeginRender() const = 0;
		virtual void EndRender() const = 0;
		virtual void OnResize(int new_width, int new_height) = 0;

	
		static ScopedPtr<Window> Create(const WindowProperties& winProp = {});


		//virtual Window* GetUnderlyingWindow() = 0;

	protected:
		uint32_t m_ScreenWidth, m_ScreenHeight;

	};

	/*template<typename T>
	class WindowImpl : public Window
	{
	public:
		T* GetUnderlyingWindow() override
		{
			return static_cast<T*>(this);
		}
	};*/




}