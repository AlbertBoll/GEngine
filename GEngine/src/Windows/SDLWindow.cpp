
#include "gepch.h"
#include "Windows/SDLWindow.h"

namespace GEngine
{

	extern SDL_DisplayMode mode;
	

	SDLWindow::~SDLWindow()
	{
	
	}

	void GEngine::SDLWindow::Initialize(const WindowProperties& winProp)
	{
		uint32_t flag = GetWindowFlag(winProp);
	

		// Set OpenGL attributes
		// Use the core OpenGL profile
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		// Specify version 4.6
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		// Request a color buffer with 8-bits per RGBA channel
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		// Enable double buffering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// Force OpenGL to use hardware acceleration
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);


		//create SDL window
		//GENGINE_CORE_INFO(SDL_WINDOWPOS_CENTERED);
		//m_Window = SDL_CreateWindow(winProp.m_Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winProp.m_Width, winProp.m_Height, flag);
		//m_Window = SDL_CreateWindow(winProp.m_Title.c_str(), winProp.m_TopLeftX, winProp.m_TopLeftY, winProp.m_Width, winProp.m_Height, flag);
		//m_Window = SDL_CreateWindow(winProp.m_Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winProp.m_Width, winProp.m_Height, flag);

		SetWindow(mode.w, mode.h, flag, winProp);
		
		ASSERT(m_Window, "SDL Window couldn't be created!");

		m_ScreenWidth = winProp.m_Width;
		m_ScreenHeight = winProp.m_Height;

		//Set Window Minimum Size
		SDL_SetWindowMinimumSize(m_Window, winProp.m_MinWidth, winProp.m_MinHeight);

		m_Context = SDL_GL_CreateContext(m_Window);
		ASSERT(m_Context, "SDL_GL context couldn't be created!");

		int success = gladLoadGL();

		//Load OpenGL Context
		ASSERT(success, "OpenGL functions coundn't be loaded!");

		
		glClearColor(winProp.m_Red, winProp.m_Green, winProp.m_Blue, 1.0f);

		//Enable depth test
		glEnable(GL_DEPTH);
		glDepthFunc(GL_LEQUAL);

		//Enable blending
		glEnable(GL_BLEND);
		glEnable(GL_MULTISAMPLE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		

		if (winProp.m_IsVsync)
		{
			//Set VSYNC;
			SDL_GL_SetSwapInterval(1);
		}

		

	}

	void GEngine::SDLWindow::SwapBuffer() const
	{
		SDL_GL_SwapWindow(m_Window);
	}

	void GEngine::SDLWindow::ShutDown() 
	{
		GENGINE_CORE_INFO("Release Window!");
	
			SDL_GL_DeleteContext(m_Context);
			SDL_DestroyWindow(m_Window);
			m_Context = nullptr;
			m_Window = nullptr;
		
		
		//SDL_Quit();
	}

	void GEngine::SDLWindow::SetTitle(const std::string& title) const
	{
		SDL_SetWindowTitle(m_Window, title.c_str());
	}

	uint32_t SDLWindow::GetWindowID() const
	{
		ASSERT(m_Window, "Window can not be null!")
		return SDL_GetWindowID(m_Window);
	}

	void SDLWindow::SetWindow(int DisplayWidth, int DisplayHeight, uint32_t flag, const WindowProperties& winProp)
	{

		int topLeftPosX{};
		int topLeftPosY{};

		switch (winProp.m_WinPos)
		{
		case WindowPos::TopLeft:
			topLeftPosX = DisplayWidth / 2 - winProp.m_Width -   winProp.m_XPaddingToCenterY;
			topLeftPosY = DisplayHeight / 2 - winProp.m_Height - winProp.m_YPaddingToCenterX;
			break;
		
		case WindowPos::TopRight:
			topLeftPosX = DisplayWidth / 2  + winProp.m_XPaddingToCenterY;
			topLeftPosY = DisplayHeight / 2 - winProp.m_Height - winProp.m_YPaddingToCenterX;
			break;

		case WindowPos::ButtomLeft:
			topLeftPosX = DisplayWidth / 2 - winProp.m_Width - winProp.m_XPaddingToCenterY;
			topLeftPosY = DisplayHeight / 2 + winProp.m_YPaddingToCenterX;
			break;

		case WindowPos::ButtomRight:
			topLeftPosX = DisplayWidth / 2  + winProp.m_XPaddingToCenterY;
			topLeftPosY = DisplayHeight / 2 + winProp.m_YPaddingToCenterX;
			break;

		case WindowPos::Center:
			topLeftPosX = DisplayWidth / 2 - winProp.m_Width / 2;
			topLeftPosY = DisplayHeight / 2 - winProp.m_Height / 2;
			break;

		}

		m_Window = SDL_CreateWindow(winProp.m_Title.c_str(), topLeftPosX, topLeftPosY, winProp.m_Width, winProp.m_Height, flag);


	}


	uint32_t SDLWindow::GetWindowFlag(const WindowProperties& winProp)
	{
		uint32_t flag = SDL_WINDOW_OPENGL;


		if (winProp.flag.IsSet(WindowFlags::INVISIBLE))
		{
			flag |= SDL_WINDOW_HIDDEN;
		}

		if (winProp.flag.IsSet(WindowFlags::FULLSCREEN))
		{
			flag |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		if (winProp.flag.IsSet(WindowFlags::BORDERLESS))
		{
			flag |= SDL_WINDOW_BORDERLESS;
		}

		if (winProp.flag.IsSet(WindowFlags::RESIZABLE))
		{
			flag |= SDL_WINDOW_RESIZABLE;
		}

		return flag;
	}

	void SDLWindow::BeginRender() const
	{
		SDL_GL_MakeCurrent(m_Window, m_Context);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}


	void SDLWindow::EndRender() const
	{
		SwapBuffer();
	}


	std::string SDLWindow::GetTitle() const
	{
		return SDL_GetWindowTitle(m_Window);
	}


	void SDLWindow::OnResize(int new_width, int new_height)
	{
		m_ScreenWidth = new_width;
		m_ScreenHeight = new_height;

	}


	

}