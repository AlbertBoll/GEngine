#pragma once

namespace GEngine
{


	class KeyboardEvent
	{

	public:
		static void OnKeyPress(SDL_KeyboardEvent& e);
		static void OnKeyRelease(SDL_KeyboardEvent& e);
		static void OnKeyRepeat(SDL_KeyboardEvent& e);

	};


}
