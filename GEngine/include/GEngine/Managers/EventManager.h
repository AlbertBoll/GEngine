#pragma once
#include "Events/Event.h"
#include "Managers/ManagerBase.h"

union SDL_Event;

namespace GEngine::Manager
{

	class EventManager: ManagerBase<EventManager>
	{
		friend class ManagerBase<EventManager>;


	public:
		static ScopedPtr<EventManager> GetScopedInstance();
		void Initialize();
		void OnEvent(SDL_Event& e);
		EventDispatcher& GetEventDispatcher() { return m_EventDispatcher; }

	private:
		friend class GEngine;
		EventManager() = default;
	
	private:
		EventDispatcher m_EventDispatcher;

	
	};

}