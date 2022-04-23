#include "Windows/SDLWindow.h"
#include "sdl2/SDL.h"
#include <glad/glad.h>

namespace GEngine
{
	void GEngine::SDLWindow::Initialize(const WindowProperties& winProp)
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

		//Initialize SDL
		GENGINE_CORE_INFO("Initialize SDL");
		SDL_Init(SDL_INIT_EVERYTHING);
		////ASSERT(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER), "SDL initialize failure");

		SDL_version version{};
		SDL_VERSION(&version);

		GENGINE_CORE_INFO("SDL {}.{}.{}", (uint32_t)version.major, (uint32_t)version.minor, (uint32_t)version.patch);
	

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
		m_Window = SDL_CreateWindow(winProp.m_Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winProp.m_Width, winProp.m_Height, flag);
		ASSERT(m_Window, "SDL Window couldn't be created!");

		m_ScreenWidth = winProp.m_Width;
		m_ScreenHeight = winProp.m_Height;

		//Set Window Minimum Size
		SDL_SetWindowMinimumSize(m_Window, winProp.m_MinWidth, winProp.m_MinHeight);

		m_Context = SDL_GL_CreateContext(m_Window);
		ASSERT(m_Context, "SDL_GL context couldn't be created!");


		//Load OpenGL Context
		ASSERT(gladLoadGL(), "OpenGL functions coundn't be loaded!");

		#ifdef GENGINE_CONFIG_DEBUG
			glClearColor(winProp.m_Red, winProp.m_Green, winProp.m_Blue, 1.0f);

			//Enable depth test
			glEnable(GL_DEPTH);

			//Enable blending
			glEnable(GL_BLEND);
			glEnable(GL_MULTISAMPLE);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		#endif

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
}