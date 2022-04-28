#pragma once

#include <unordered_map>
#include "Window.h"


namespace GEngine
{

	class WindowManager
	{
		
	public:

		
		NONCOPYMOVABLE(WindowManager);//Mark WindowManager is non copyable and non movable
		~WindowManager();
		static WindowManager& Get();
		//void Initialize();
		Window* GetInternalWindow(uint32_t ID){ return m_Windows.at(ID).get(); }

		std::unordered_map<uint32_t, ScopedPtr<Window>>& GetWindows() { return m_Windows; }

		void AddWindow(const std::string& title = "GEngine Editor App");

		template<typename T = WindowProperties, typename ... Args>
		void AddWindows(const T& winProp = WindowProperties{}, Args&&... args);

		void AddWindows(const WindowProperties& winProp = WindowProperties{});

		void AddWindows(const std::initializer_list<WindowProperties>& winProps);


	private:
		friend class GEngine;
		WindowManager() = default;

	private:
		std::unordered_map<uint32_t, ScopedPtr<Window>> m_Windows{};
		uint8_t m_NumOfWindows{};
	};

	template<typename T, typename ...Args>
	inline void WindowManager::AddWindows(const T& winProp, Args && ...args)
	{
		AddWindows(winProp);
		AddWindows(std::forward<Args>(args)...);
	}


}