#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace MABEngine {
	namespace Logging {
		std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
		std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

		void Log::Init(LogSetting coreLogSetting, LogSetting appLogSetting) {
			spdlog::set_pattern("%^[%T] %n: %v%$");

			s_CoreLogger = spdlog::stdout_color_mt(coreLogSetting.GetLoggerName());
			s_CoreLogger->set_level(coreLogSetting.GetLoggerLevel());

			s_ClientLogger = spdlog::stdout_color_mt(appLogSetting.GetLoggerName());
			s_ClientLogger->set_level(appLogSetting.GetLoggerLevel());
		}
	}
}