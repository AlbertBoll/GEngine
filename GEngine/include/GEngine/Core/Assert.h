#pragma once

#include "BaseUtility.h"
#include "Log.h"
#include <filesystem>


#ifdef GENGINE_ENABLE_ASSERTS
	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define GENGINE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { GENGINE##type##ERROR(msg, __VA_ARGS__); GENGINE_DEBUGBREAK(); } }
	#define GENGINE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) GENGINE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define GENGINE_INTERNAL_ASSERT_NO_MSG(type, check) GENGINE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", GENGINE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define GENGINE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define GENGINE_INTERNAL_ASSERT_GET_MACRO(...) GENGINE_EXPAND_MACRO( GENGINE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, GENGINE_INTERNAL_ASSERT_WITH_MSG, GENGINE_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define GENGINE_ASSERT(...) GENGINE_EXPAND_MACRO( GENGINE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define GENGINE_CORE_ASSERT(...) GENGINE_EXPAND_MACRO( GENGINE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )

#else
	#define GENGINE_ASSERT(...)
	#define GENGINE_CORE_ASSERT(...)


#endif