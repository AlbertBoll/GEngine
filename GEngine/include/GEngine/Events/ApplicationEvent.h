#pragma once


namespace GEngine::Event
{

	class ApplicationEvent
	{

	public:
		static void OnWindowClose(SDL_WindowEvent& e);
		static void OnWindowResize(SDL_WindowEvent& e);
		static void OnAppQuit();

	};

}
