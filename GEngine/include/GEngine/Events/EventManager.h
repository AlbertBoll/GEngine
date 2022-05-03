#pragma once



namespace GEngine::Event
{
	class EventManager
	{

	public:
		static void OnUpdate(SDL_Event& e);
	
	private:

		//inline static MouseEvent s_MouseEvent;
		//inline static KeyboardEvent s_KeyboardEvent;
		//inline static ApplicationEvent s_ControllerEvent;

	
	};

}