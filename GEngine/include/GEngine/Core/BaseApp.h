#pragma once

#include "GEngine.h"
#include "Timestep.h"


namespace GEngine
{
	class BaseApp
	{
		
	public:
		BaseApp() = default;

		NONCOPYMOVABLE(BaseApp);

		virtual ~BaseApp();

	    static GEngine& GetEngine(){ return m_GEngine;};

	    WindowManager& GetWindowManager() { return m_GEngine.GetWindowManager(); };
	    void Initialize();
		
		virtual void Update(Timestep ts){};
		virtual void ProcessInput(Timestep ts){};
		virtual void Run();
		void ShowDown()const { m_GEngine.ShutDown(); }
		
	private:
		inline static GEngine m_GEngine;

	};




}