
#include <iostream>
#include "GEngine/Core/GEngine.h"





int main(int argc, char* args[])
{



	//constexpr BitFlags<WindowFlags, uint8_t> flag(WindowFlags::BORDERLESS, WindowFlags::FULLSCREEN);
	//constexpr BitFlags<WindowFlags, uint8_t> flag_(WindowFlags::BORDERLESS, WindowFlags::INVISIBLE);
	//std::cout << std::boolalpha;
	//std::cout << flag.IsSet(WindowFlags::BORDERLESS) << std::endl;

	//std::cout << "Jellp" << std::endl;

	//std::cout << p->m_X << std::endl;
		//Timeit(main);
	
	GEngine::GEngine Engine;
	Engine.Initialize();
	Engine.Run();
	return 0;

}