#include "gepch.h"
#include "Events/EventManager.h"
#include "Events/MouseEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/ApplicationEvent.h"

namespace GEngine
{


	void GEngine::EventManager::OnUpdate(SDL_Event& e)
	{

		while(SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:

				ApplicationEvent::OnAppQuit();
				break;

			case SDL_KEYDOWN:
				if(!e.key.repeat) KeyboardEvent::OnKeyPress(e.key);
				else KeyboardEvent::OnKeyRepeat(e.key);
				break;

			case SDL_KEYUP:
				KeyboardEvent::OnKeyRelease(e.key);
				break;

			case SDL_MOUSEBUTTONDOWN:
				MouseEvent::OnMouseButtonClick(e.button);
				break;

			case SDL_MOUSEBUTTONUP:
				MouseEvent::OnMouseButtonRelease(e.button);
				break;

			case SDL_MOUSEWHEEL:
				MouseEvent::OnMouseWheel(e.wheel);
				break;

			case SDL_MOUSEMOTION:
				MouseEvent::OnMouseMove(e.motion);
				break;

			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_CLOSE) ApplicationEvent::OnWindowClose(e.window);
				else if (e.window.event == SDL_WINDOWEVENT_RESIZED) ApplicationEvent::OnWindowResize(e.window);
				break;

			}
		}
	}


}