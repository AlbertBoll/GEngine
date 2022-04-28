#include "gepch.h"
#include "Windows/WindowManager.h"
#include "Windows/SDLWindow.h"

namespace GEngine
{
	WindowManager::~WindowManager()
	{
		for (auto& p : m_Windows)
		{
			if (p.second)
			{
				p.second->ShutDown();
			}
		}
	}

	WindowManager& WindowManager::Get()
	{
		static WindowManager windowManager;
		return windowManager;
	}

	void WindowManager::AddWindow(const std::string& title)
	{
		auto windowPtr = CreateScopedPtr<SDLWindow>();
		windowPtr->Initialize();
		windowPtr->SetTitle(title);
		uint32_t ID = windowPtr->GetWindowID();
		m_Windows.insert({ ID, std::move(windowPtr) });
		m_NumOfWindows++;
	}

	void WindowManager::AddWindows(const WindowProperties& winProp)
	{
		GENGINE_CORE_INFO("Initialize Windows...");
		auto windowPtr = CreateScopedPtr<SDLWindow>();
		windowPtr->Initialize(winProp);

		uint32_t ID = windowPtr->GetWindowID();
		m_Windows.insert({ ID, std::move(windowPtr) });
		m_NumOfWindows++;
	}

	void WindowManager::AddWindows(const std::initializer_list<WindowProperties>& winProps)
	{
		for (auto& p : winProps)
		{
			AddWindows(p);
		}
	}
}
