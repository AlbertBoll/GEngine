#pragma once

#include "Utility.h"
#include "../Inputs/InputManager.h"
#include "WindowManager.h"

namespace GEngine
{

	class GEngine
	{

	public:
		NONCOPYMOVABLE(GEngine);
		~GEngine();
		static GEngine& Get();
		void Initialize();
		WindowManager* GetWindowManager();
		//void Run();
		void Run();
		void ShutDown();
		bool IsRunning()const { return m_Running; }
		//bool SetIsRunning(bool run) { m_Running = run; }

	private:
		friend class BaseApp;
		GEngine() = default;
		void GetEnvironmentInfo() const;

	private:
		ScopedPtr<InputManager> m_InputManager{};
		ScopedPtr<WindowManager> m_WindowManager{};
		bool m_IsInitialize{ false };
		bool m_Running{ true };

	};


}
