#include "gepch.h"
#include "Events/ApplicationEvent.h"
#include "Core/BaseApp.h"


namespace GEngine::Event
{

	void ApplicationEvent::OnWindowClose(SDL_WindowEvent& e)
	{
		auto& engine = BaseApp::GetEngine();
		auto* windowsManager = engine.GetWindowManager();
		if (auto p = windowsManager->GetWindows().find(e.windowID); p != windowsManager->GetWindows().end())
		{
			GENGINE_CORE_INFO("Window with ID {} was closed", e.windowID);
			windowsManager->RemoveWindow(e.windowID);
			GENGINE_CORE_INFO("Window Manager Size {}", windowsManager->GetWindows().size());

			auto& numWindows = windowsManager->GetNumOfWindows();
			if (--numWindows == 0) {
				engine.ShutDown();
				GENGINE_CORE_INFO("ShutDown!");

			}
		}

	}


	void ApplicationEvent::OnWindowResize(SDL_WindowEvent& e)
	{
		auto new_width = e.data1;
		auto new_height = e.data2;
		auto& engine = BaseApp::GetEngine();
		auto* windowsManager = engine.GetWindowManager();

		if (auto p = windowsManager->GetWindows().find(e.windowID); p != windowsManager->GetWindows().end())
		{
			p->second->OnResize(new_width, new_height);
			//GENGINE_CORE_INFO("Window with title {} has been resized to ({}, {})", p->second->GetTitle(), new_width, new_height);
		}

	}


	void ApplicationEvent::OnAppQuit()
	{
		auto& engine = BaseApp::GetEngine();
		engine.ShutDown();
	}
}