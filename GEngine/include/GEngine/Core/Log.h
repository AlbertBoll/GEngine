#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include "Utility.h"

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

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}



#ifdef GENGINE_CONFIG_DEBUG

//  Core Engine side log macros
	#define GENGINE_CORE_TRACE(...)    :: GEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define GENGINE_CORE_INFO(...)     :: GEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define GENGINE_CORE_WARN(...)     :: GEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define GENGINE_CORE_ERROR(...)    :: GEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define GENGINE_CORE_CRITICAL(...) :: GEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)
									
	// Client side log macros			
	#define GENGINE_TRACE(...)         :: GEngine::Log::GetLogger()->trace(__VA_ARGS__)
	#define GENGINE_INFO(...)          :: GEngine::Log::GetLogger()->info(__VA_ARGS__)
	#define GENGINE_WARN(...)          :: GEngine::Log::GetLogger()->warn(__VA_ARGS__)
	#define GENGINE_ERROR(...)         :: GEngine::Log::GetLogger()->error(__VA_ARGS__)
	#define GENGINE_CRITICAL(...)      :: GEngine::Log::GetLogger()->critical(__VA_ARGS__)

#else 
	#define GENGINE_CORE_TRACE(...)    (void)0
	#define GENGINE_CORE_INFO(...)     (void)0
	#define GENGINE_CORE_WARN(...)     (void)0
	#define GENGINE_CORE_ERROR(...)    (void)0
	#define GENGINE_CORE_CRITICAL(...) (void)0
									  
// Client log macros				  
	#define GENGINE_TRACE(...)         (void)0
	#define GENGINE_INFO(...)          (void)0
	#define GENGINE_WARN(...)          (void)0
	#define GENGINE_ERROR(...)         (void)0
	#define GENGINE_CRITICAL(...)      (void)0

	
	

#endif