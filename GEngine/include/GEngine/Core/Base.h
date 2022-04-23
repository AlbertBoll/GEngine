#pragma once

#include <memory>



#ifdef GENGINE_CONFIG_DEBUG
	#if defined(GENGINE_PLATFORM_WINDOWS)
		#define GENGINE_DEBUGBREAK() __debugbreak()

	#elif defined(GENGINE_PLATFORM_LINUX)
		//#include<signal.h>
		//#define GENGINE_DEBUGBREAK() raise(SIGTRAP)
		#define GENGINE_DEBUGBREAK() __builtin_trap();
	
	#elif defined(GENGINE_PLATFORM_MAC)
		#define GENGINE_DEBUGBREAK() __builtin_debugtrap();

	//not yet support any other platforms
	#else
		#error "Platform doesn't support debugbreak yet!"
	
	#endif
	#define GENGINE_ENABLE_ASSERTS
	
#else
	#define GENGINE_DEBUGBREAK()

#endif

#define GENGINE_EXPAND_MACRO(str) str
#define GENGINE_STRINGIFY_MACRO(str) #str

#define BIT(x) (1 << x)

#define BENGINE_BIND_EVENT(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }







#include "Core/Log.h"
#include "Core/Assert.h"