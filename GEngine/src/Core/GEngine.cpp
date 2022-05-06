#include "gepch.h"
#include "Core/GEngine.h"



namespace GEngine
{

	SDL_DisplayMode mode;


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

			GENGINE_CORE_INFO("Initialize Window Manager");
			
			m_WindowManager = Manager::WindowManager::GetScopedInstance();


			GENGINE_CORE_INFO("Initialize Input Manager");
			
			m_InputManager = Manager::InputManager::GetScopedInstance();
			m_InputManager->Initialize();

			GENGINE_CORE_INFO("Initialize Event Manager");

			m_EventManager = Manager::EventManager::GetScopedInstance();
			m_EventManager->Initialize();

			m_IsInitialize = true;
			
		}
	}


	void GEngine::Run()
	{
		
		SDL_Event event;

		while (m_Running) {

			m_EventManager->OnEvent(event);

			for (auto& p : m_WindowManager->GetWindows())
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