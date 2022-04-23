#include "Core/GEngine.h"
#include "sdl2/SDL.h"
#include "Core/Log.h"
#include <iostream>
#include <Windows/SDLWindow.h>


namespace GEngine
{


	GEngine::~GEngine()
	{
		if (m_Window) {
			m_Window->ShutDown();
		}
	}

	void GEngine::GetEnvironmentInfo()const
	{
		#if defined(GENGINE_CONFIG_DEBUG)
				GENGINE_CORE_INFO("Configuration: DEBUG");
		
		#elif defined(GENGINE_CONFIG_RELEASE)
				GENGINE_CORE_INFO("Configuration: RELEASE");
		
		#endif
		
		#if defined(GENGINE_PLATFORM_WINDOWS)
				GENGINE_CORE_INFO("Platform: WINDOWS");
		
		#elif defined(GENGINE_PLATFORM_MAC)
				GENGINE_CORE_INFO("Platform: MACOSX");
		
		#else
				GENGINE_CORE_INFO("Platform: LINUX");
		
		#endif
	}

	void GEngine::Initialize(const WindowProperties& winProp)
	{

	
		if (!m_IsInitialize)
		{
			Log::Initialize();
			GENGINE_CORE_INFO("Initialize Logging...");
			GENGINE_CORE_INFO("GEngine v{}.{}", 1, 0);

			//Get environment Info
			GetEnvironmentInfo();

			GENGINE_CORE_INFO("Initialize Window...");
			m_Window = CreateScopedPtr<SDLWindow>();
			m_Window->Initialize(winProp);

			m_IsInitialize = true;

		}
	}

	void GEngine::Run()
	{
		SDL_Event event;

		while (m_Running) {
			
			while (SDL_PollEvent(&event)) {
				switch (event.type)
				{
				case SDL_QUIT:
					m_Running = false;
					break;
				}
			}
		}
	}

	bool Initialize()
	{
		
		Log::Initialize();
		GENGINE_CORE_INFO("GEngine v{}.{}", 1, 0);
		//GENGINE_ASSERT(SDL_Init(SDL_INIT_EVERYTHING) < 0, "something wrong")

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			
			std::cout << "Error initializing SDL2: " << SDL_GetError() << std::endl;
			return false;
		}

		else
		{
			SDL_version version{};
			SDL_VERSION(&version);

			GENGINE_CORE_INFO("SDL {}.{}.{}", (uint32_t)version.major, (uint32_t)version.minor, (uint32_t)version.patch);
			return true;
		}
	}


}