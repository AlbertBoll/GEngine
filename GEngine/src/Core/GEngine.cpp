#include "gepch.h"
#include "Core/GEngine.h"



namespace GEngine
{

	SDL_DisplayMode mode;


	GEngine::~GEngine()
	{
		/*if (m_WindowManager)
		{
			delete m_WindowManager;
			m_WindowManager = nullptr;
		}*/
	
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

			
			m_IsInitialize = true;

		}
	}


	void GEngine::Run()
	{
		SDL_Event event;

		while (m_Running) {

			while (SDL_PollEvent(&event)) {

				if (event.type == SDL_MOUSEMOTION)
				{
					if (auto p = m_WindowManager.m_Windows.find(event.motion.windowID); p != m_WindowManager.m_Windows.end())
					{
						GENGINE_CORE_INFO("Mouse moves to the {}. xPos: {}   yPos: {}", p->second->GetTitle(), event.motion.x, event.motion.y);
					}
				}

				if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					if (auto p = m_WindowManager.m_Windows.find(event.window.windowID); p != m_WindowManager.m_Windows.end())
					{

						p->second->ShutDown();

						if (--m_WindowManager.m_NumOfWindows == 0) {
							ShutDown();
							break;
						}

					}
				}

				for (auto& p : m_WindowManager.m_Windows)
				{

					p.second->BeginRender();
					p.second->EndRender();
				}


			}


		}

	}


	void GEngine::ShutDown()
	{
		m_Running = false;
	}


}