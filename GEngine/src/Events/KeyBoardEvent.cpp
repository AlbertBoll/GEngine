#include "gepch.h"
#include "Events/KeyboardEvent.h"


namespace GEngine
{
	void KeyboardEvent::OnKeyPress(SDL_KeyboardEvent& e)
	{
		GENGINE_CORE_INFO("Key {} was pressed", SDL_GetKeyName(e.keysym.sym));
	}


	void KeyboardEvent::OnKeyRelease(SDL_KeyboardEvent& e)
	{
		GENGINE_CORE_INFO("Key {} was released", SDL_GetKeyName(e.keysym.sym));
	}


	void KeyboardEvent::OnKeyRepeat(SDL_KeyboardEvent& e)
	{
		GENGINE_CORE_INFO("Key {} was repeated", SDL_GetKeyName(e.keysym.sym));
	}
}
