#include "GEngine.h"
#include <iostream>

namespace GEngine
{
	int Add(int a, int b)
	{
		return a + b;
	}

	void GetInfo()
	{
		#if defined(GENGINE_CONFIG_DEBUG)
			std::cout << "Configuration: DEBUG" << std::endl;
		#elif defined(GENGINE_CONFIG_RELEASE)
			std::cout << "Configuration: RELEASE" << std::endl;
		#endif

		#if defined(GENGINE_PLATFORM_WINDOWS)
			std::cout << "Platform: WINDOWS" << std::endl;
		#elif defined(GENGINE_PLATFORM_MAC)
			std::cout << "Platform: MACOSX" << std::endl;
		#else
			std::cout << "Platform: LINUX" << std::endl;
		#endif

	}
}