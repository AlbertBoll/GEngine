#include "GEngine.h"
#include "sdl2/SDL.h"
#include <iostream>


namespace GEngine
{

	void GetInfo()
	{
		#if defined(GENGINE_CONFIG_DEBUG)
			std::cout << "Configuration: DEBUG" << std::endl;
		#elif defined(GENGINE_CONFIG_RELEASE)
			std::cout << "Configuration: RELEASE" << std::endl;
		#endif

		#if defined(GENGINE_PLATFORM_WINDOWS)
			std::cout << "Platform: WINDOWS" << std::endl;
		#elif defined(GENGINE_PLATFORM_MAC)
			std::cout << "Platform: MACOSX" << std::endl;
		#else
			std::cout << "Platform: LINUX" << std::endl;
		#endif

	}
	bool Initialize()
	{

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cout << "Error initializing SDL2: " << SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			SDL_version version;
			SDL_VERSION(&version);
			std::cout << "SDL " << (uint32_t)version.major << "." << (uint32_t)version.minor << "." << (uint32_t)version.patch << std::endl;
			return true;
		}
	}

	void Shutdown()
	{
		SDL_Quit();
	}
}