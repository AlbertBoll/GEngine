#include "gepch.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace GEngine
{

	//RefPtr<spdlog::logger> Log::s_CoreLogger;
	//RefPtr<spdlog::logger> Log::s_Logger;

	void Log::Initialize()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(CreateRefPtr<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(CreateRefPtr<spdlog::sinks::basic_file_sink_mt>("GEngine.log", true));

		logSinks[0]->set_pattern("%^[%D %T] %n: %v%$");
		logSinks[1]->set_pattern("[%D %T] [%l] %n: %v");

		s_CoreLogger = CreateRefPtr<spdlog::logger>("GENGINE", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_Logger = CreateRefPtr<spdlog::logger>("APP", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_Logger);
		s_Logger->set_level(spdlog::level::trace);
		s_Logger->flush_on(spdlog::level::trace);
	}
}