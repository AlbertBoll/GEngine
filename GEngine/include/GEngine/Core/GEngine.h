#pragma once

#include "Utility.h"
#include "Managers/InputManager.h"
#include "Managers/WindowManager.h"
#include <Managers/EventManager.h>




namespace GEngine
{

	class GEngine
	{

	public:
		NONCOPYMOVABLE(GEngine);
		~GEngine();
		static GEngine& Get();
		void Initialize();
		Manager::WindowManager* GetWindowManager() { return m_WindowManager.get(); }
		Manager::InputManager* GetInputManager() { return m_InputManager.get(); }
		Manager::EventManager* GetEventManager() { return m_EventManager.get(); }
		void Run();
		void ShutDown();
		bool IsRunning()const { return m_Running; }

	private:
		friend class BaseApp;
		GEngine() = default;
		void GetEnvironmentInfo() const;

	private:
	
		ScopedPtr<Manager::InputManager> m_InputManager{};
		ScopedPtr<Manager::WindowManager> m_WindowManager{};
		ScopedPtr<Manager::EventManager> m_EventManager{};

		bool m_IsInitialize{ false };
		bool m_Running{ true };

	};


}
