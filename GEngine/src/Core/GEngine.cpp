#include "gepch.h"
#include "Core/GEngine.h"
#include <Events/EventManager.h>
//#include "Inputs/InputManager.h"
//#include "core/WindowManager.h"

namespace GEngine
{

	SDL_DisplayMode mode;


	GEngine::~GEngine()
	{

		//since using scoped pointer, there is no need to release resource in destructor
		/*if (m_WindowManager)
		{
			delete m_WindowManager;
			m_WindowManager = nullptr;
		}*/

		//delete m_InputManager;
		//delete m_WindowManager;
	
	}

	GEngine& GEngine::Get()
	{
		static GEngine G_Engine;
		return G_Engine;
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

	void GEngine::Initialize()
	{

	
		if (!m_IsInitialize)
		{
			Log::Initialize();
			GENGINE_CORE_INFO("Initialize Logging...");
			GENGINE_CORE_INFO("GEngine v{}.{}", 1, 0);

			//Get environment Info
			GetEnvironmentInfo();

			//Initialize SDL
			GENGINE_CORE_INFO("Initialize SDL");


			//
			//SDL_Init(SDL_INIT_EVERYTHING);
			int code = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

			ASSERT(!code, "SDL initialize failure");

			SDL_version version{};
			SDL_VERSION(&version);

			GENGINE_CORE_INFO("SDL {}.{}.{}", (uint32_t)version.major, (uint32_t)version.minor, (uint32_t)version.patch);

			//SDL_DisplayMode mode;
			SDL_GetDesktopDisplayMode(0, &mode);
			GENGINE_CORE_INFO("Display width: {}. Display height: {}. Refresh Rate: {}", mode.w, mode.h, mode.refresh_rate);

			GENGINE_CORE_INFO("Initialize WindowManager");
			
			m_WindowManager = WindowManager::GetScopedInstance();

			GENGINE_CORE_INFO("Initialize InputManager");
			
			m_InputManager = InputManager::GetScopedInstance();
			m_InputManager->Initialize();

			m_IsInitialize = true;
			
		}
	}


	void GEngine::Run()
	{
		
		SDL_Event event;

		while (m_Running) {

	
			m_InputManager->ProcessEvent(event);
			

			for (auto& p : m_WindowManager->m_Windows)
			{

				p.second->BeginRender();
				p.second->EndRender();
			}
		}


	}


	void GEngine::ShutDown()
	{
		m_Running = false;
	}


}