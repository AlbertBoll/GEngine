#pragma once

#include "BaseUtility.h"
#include "Window.h"

namespace GEngine
{
	class GEngine
	{
	public:

		GEngine() = default;
		NONCOPYMOVABLE(GEngine);
		~GEngine();
		void GetEnvironmentInfo() const;
		void Initialize(const WindowProperties& winProp = WindowProperties{});
		Window* GetInternalWindow()const { return m_Window.get(); }
		void Run();
		

	private:
		ScopedPtr<Window>m_Window{};
		volatile bool m_IsInitialize{false};
		volatile bool m_Running{ true };

	};
}
