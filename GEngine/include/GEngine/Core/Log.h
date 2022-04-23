#pragma once


#include "BaseUtility.h"

#include <spdlog/spdlog.h>


namespace GEngine
{
	class Log
	{

	public:
		static void Initialize();

		
		inline static RefPtr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		inline static RefPtr<spdlog::logger>& GetLogger() { return s_Logger; }

	private:
		inline static RefPtr<spdlog::logger> s_CoreLogger;
		inline static RefPtr<spdlog::logger> s_Logger;
	};

}

// Core log macros
#define GENGINE_CORE_TRACE(...)    :: GEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GENGINE_CORE_INFO(...)     :: GEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GENGINE_CORE_WARN(...)     :: GEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GENGINE_CORE_ERROR(...)    :: GEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GENGINE_CORE_CRITICAL(...) :: GEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)
								
// Client log macros			
#define GENGINE_TRACE(...)         :: GEngine::Log::GetLogger()->trace(__VA_ARGS__)
#define GENGINE_INFO(...)          :: GEngine::Log::GetLogger()->info(__VA_ARGS__)
#define GENGINE_WARN(...)          :: GEngine::Log::GetLogger()->warn(__VA_ARGS__)
#define GENGINE_ERROR(...)         :: GEngine::Log::GetLogger()->error(__VA_ARGS__)
#define GENGINE_CRITICAL(...)      :: GEngine::Log::GetLogger()->critical(__VA_ARGS__)