#pragma once

#include <unordered_map>
#include "Window.h"
#include "ManagerBase.h"

namespace GEngine
{

	class WindowManager: public ManagerBase<WindowManager>
	{
		//declare friend ManagerBase to invoke managerbase Get()    
		friend class ManagerBase<WindowManager>;

	public:
		
		
		~WindowManager();
		static ScopedPtr<WindowManager> GetScopedInstance();

		//void Initialize();
		Window* GetInternalWindow(uint32_t ID){ return m_Windows.at(ID).get(); }

		std::unordered_map<uint32_t, ScopedPtr<Window>>& GetWindows() { return m_Windows; }

		void AddWindow(const std::string& title = "GEngine Editor App");

		template<typename T = WindowProperties, typename ... Args>
		void AddWindows(const T& winProp = WindowProperties{}, Args&&... args);

		void AddWindows(const WindowProperties& winProp = WindowProperties{});

		void AddWindows(const std::initializer_list<WindowProperties>& winProps);

		uint8_t& GetNumOfWindows() { return m_NumOfWindows; }
		uint8_t GetNumOfWindows()const { return m_NumOfWindows; }

		void RemoveWindow(uint32_t ID);


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