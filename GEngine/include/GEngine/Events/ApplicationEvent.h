#pragma once


namespace GEngine
{

	class ApplicationEvent
	{

	public:
		static void OnWindowClose(SDL_WindowEvent& e);
		static void OnWindowResize(SDL_WindowEvent& e);
		static void OnAppQuit();

	};

}
