#include "mabengine_pch.h"
#include "LogSetting.h"


namespace MABEngine {
	namespace Logging {

		std::string LogSetting::ToString() {
			std::string names[] = { "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "CRITICAL", "OFF" };

			// Make sure to check mLogLevel is within bounds to prevent out-of-range access
			std::string logLevelName = (mLevel >= 0 && mLevel < sizeof(names) / sizeof(names[0]))
				? names[mLevel]
				: "UNKNOWN";

			return std::string("Logger Name is '"+ mLoggerName + "' - Log Level is '" + logLevelName + "'");
		}

	}
}