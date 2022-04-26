#pragma once

#include "Window.h"
#include <unordered_map>


namespace GEngine
{
	class GEngine
	{
	public:

		
		NONCOPYMOVABLE(GEngine);
		~GEngine();
		static GEngine& Get();
		//void Initialize(const WindowProperties& winProp = WindowProperties{}, bool IsMultipleWindows);
		void Initialize();
		Window* GetInternalWindow(uint32_t ID)const { return m_Windows.at(ID).get(); }

		void AddWindow(const std::string & title = "GEngine Editor App");

		template<typename T = WindowProperties, typename ... Args>
		void AddWindows(const T& winProp = WindowProperties{}, Args&&... args);

		void AddWindows(const WindowProperties& winProp = WindowProperties{});

		void AddWindows(const std::initializer_list<WindowProperties>& winProps);

		void Run();
		void ShutDown();

		bool IsRunning()const { return m_Running; }



	private:

		friend class BaseApp;
		GEngine() = default;
		void GetEnvironmentInfo() const;

	private:

		std::unordered_map<uint32_t, ScopedPtr<Window>> m_Windows;
		//std::vector<ScopedPtr<Window>> m_Windows;
		ScopedPtr<Window>m_Window{};
		ScopedPtr<Window>m_Window2{};
		volatile bool m_IsInitialize{false};
		volatile bool m_Running{ true };
		volatile uint8_t m_NumOfWindows{};
	};

	template<typename T, typename ...Args>
	inline void GEngine::AddWindows(const T& winProp, Args && ...args)
	{
		AddWindows(winProp);
		AddWindows(std::forward<Args>(args)...);

	}
}
