#pragma once

#include "MABEngine/Core/Base.h"
#include "spdlog/spdlog.h"

#define MABENGINE_LOG_LEVEL_TRACE 0
#define MABENGINE_LOG_LEVEL_DEBUG 1
#define MABENGINE_LOG_LEVEL_INFO 2
#define MABENGINE_LOG_LEVEL_WARN 3
#define MABENGINE_OG_LEVEL_ERROR 4
#define MABENGINE_LOG_LEVEL_CRITICAL 5
#define MABENGINE_LOG_LEVEL_OFF 6

namespace MABEngine {
	namespace Logging {

		enum MABENGINE_API LogLevel : int {
			trace = MABENGINE_LOG_LEVEL_TRACE,
			debug = MABENGINE_LOG_LEVEL_DEBUG,
			info = MABENGINE_LOG_LEVEL_INFO,
			warn = MABENGINE_LOG_LEVEL_WARN,
			err = MABENGINE_OG_LEVEL_ERROR,
			critical = MABENGINE_LOG_LEVEL_CRITICAL,
			off = MABENGINE_LOG_LEVEL_OFF,
			n_levels
		};


		class MABENGINE_API LogSetting {
		public:
			LogSetting() = delete;

			LogSetting(std::string name, LogLevel level)
				: mLoggerName(name), mLevel(static_cast<spdlog::level::level_enum>(level)) {}

			std::string ToString();

			inline const std::string& GetLoggerName() { return mLoggerName; }
			inline const spdlog::level::level_enum& GetLoggerLevel() { return mLevel; }
		private:
			std::string mLoggerName;
			spdlog::level::level_enum mLevel;
		};

	}
}

