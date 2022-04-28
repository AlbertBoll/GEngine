#pragma once

#include "Utility.h"
#include "../Windows/WindowManager.h"


namespace GEngine
{
	class GEngine
	{
	public:
		NONCOPYMOVABLE(GEngine);
		~GEngine();
		static GEngine& Get();
		void Initialize();
		WindowManager& GetWindowManager() { return m_WindowManager; }
		void Run();
		void ShutDown();
		bool IsRunning()const { return m_Running; }


	private:
		friend class BaseApp;
		GEngine() = default;
		void GetEnvironmentInfo() const;

	private:

		WindowManager m_WindowManager;
		bool m_IsInitialize{ false };
		bool m_Running{ true };

	};


}
