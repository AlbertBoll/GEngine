#pragma once

#include "Timestep.h"
#include "GEngine.h"

namespace GEngine
{
	class BaseApp
	{
		
	public:
		BaseApp() = default;

		NONCOPYMOVABLE(BaseApp);

		virtual ~BaseApp();

		static GEngine& GetEngine() { return m_GEngine; };
		static void Initialize();

		template<typename T = WindowProperties, typename ... Args>
		static void AddWindows(const T& winProp = WindowProperties{}, Args&&... args);

		static void AddWindows(const WindowProperties& winProp = WindowProperties{});

		void AddWindows(const std::initializer_list<WindowProperties>& winProps);

		virtual void Update(Timestep ts){};
		virtual void ProcessInput(Timestep ts){};
		virtual void Run();
		void ShowDown()const { m_GEngine.ShutDown(); }
		
	private:
		inline static GEngine m_GEngine;

	};

	template<typename T, typename ...Args>
	inline void BaseApp::AddWindows(const T& winProp, Args&& ...args)
	{
		m_GEngine.AddWindows(winProp, std::forward<Args>(args)...);
	}


}