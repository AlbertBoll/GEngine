#include "gepch.h"
#include "Core/GEngine.h"
#include <Windows/SDLWindow.h>


namespace GEngine
{

	SDL_DisplayMode mode;


	GEngine::~GEngine()
	{

		/*for (auto&& p : m_Windows)
		{
			if(p)
				p->ShutDown();
		}*/

		

		for (auto& p : m_Windows)
		{
			if (p.second)
			{
				p.second->ShutDown();
			}
		}
		/*if (m_Window) {
			m_Window->ShutDown();
		}

		if (m_Window2) {
			m_Window2->ShutDown();
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

			//GENGINE_CORE_INFO("Initialize Windows...");
			
		/*	if (!IsMultipleWindows)
			{
				AddWindow(winProp);
			}*/

			m_IsInitialize = true;

		}
	}

	void GEngine::AddWindow(const std::string& title)
	{
		auto windowPtr = CreateScopedPtr<SDLWindow>();
		windowPtr->Initialize();
		windowPtr->SetTitle(title);
		uint32_t ID = windowPtr->GetWindowID();
		m_Windows.insert({ ID, std::move(windowPtr)});
		m_NumOfWindows++;
		
	}

	void GEngine::AddWindows(const std::initializer_list<WindowProperties>& winProps)
	{
		
		for (auto&& p : winProps)
		{
			AddWindows(p);
		}
	}

	void GEngine::AddWindows(const WindowProperties& winProp)
	{

		GENGINE_CORE_INFO("Initialize Windows...");
		auto windowPtr = CreateScopedPtr<SDLWindow>();
		windowPtr->Initialize(winProp);
		
		uint32_t ID = windowPtr->GetWindowID();
		m_Windows.insert({ ID, std::move(windowPtr) });
		m_NumOfWindows++;
	}



	void GEngine::Run()
	{
		SDL_Event event;

		while (m_Running) {
			
			while (SDL_PollEvent(&event)) {

				if (event.type == SDL_MOUSEMOTION)
				{
					if (auto p = m_Windows.find(event.motion.windowID); p != m_Windows.end())
					{
						GENGINE_CORE_INFO("Mouse moves to the {}. xPos: {}   yPos: {}", p->second->GetTitle(), event.motion.x, event.motion.y);
					}
				}

				if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					if (auto p = m_Windows.find(event.window.windowID); p != m_Windows.end())
					{
						
						p->second->ShutDown();

						if (--m_NumOfWindows == 0) {
							ShutDown();
							break;
						}

						break;
					}
					//for(auto && p: m)
					//if (m_Window->GetWindowID() == event.window.windowID)
					//{
						//m_Running = false;
						//m_Window->ShutDown();
						//break;
					//}

					//if (m_Window2->GetWindowID() == event.window.windowID)
					//{
						//m_Window2->ShutDown();
						//break;
					//}
				
					//if (SDL_GetWindowID(m_Window) == e.window.windowID)
					//{
						// ... close window A ...
					//}
				}
				//switch (event.type)
				//{
				//case (SDL_WINDOWEVENT && event.window 
				///*case SDL_QUIT:
				//	GENGINE_CORE_INFO("Quit...");
				//	m_Running = false;
				//	break;*/
				//}
			}

			for (auto& p : m_Windows)
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