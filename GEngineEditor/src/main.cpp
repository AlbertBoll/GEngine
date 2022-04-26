
#include <iostream>
#include <GEngine/Core/BaseApp.h>




int main(int argc, char* args[])
{

	GEngine::BaseApp app;


	GEngine::WindowProperties winProp1{ .m_Title = "GEngine Editor App1",
									    .m_WinPos = GEngine::WindowPos::TopLeft,
									    .m_XPaddingToCenterY = 5,
									    .m_YPaddingToCenterX = 20,
									 };

	GEngine::WindowProperties winProp2{ .m_Title = "GEngine Editor App2",
								        .m_WinPos = GEngine::WindowPos::TopRight,
								        .m_XPaddingToCenterY = 5,
								        .m_YPaddingToCenterX = 20,
	};

	app.Initialize();
	app.AddWindows(winProp1, winProp2);

	app.Run();


	return 0;

}