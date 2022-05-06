#include <iostream>
#include <GEngine/Core/BaseApp.h>



struct WindowParams
{
	int width, height;
};

//using namespace GEngine;


int main(int argc, char* args[])
{
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	


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
	auto& engine = app.GetEngine();
	engine.GetWindowManager()->AddWindows(winProp1, winProp2);

	app.Run();
	
	std::cout << "Finish" << std::endl;

	return 0;

}