#pragma once

#include <memory.h>

#include "MABEngine/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include "LogSetting.h"

namespace MABEngine {
	namespace Logging {
		class MABENGINE_API Log
		{
		public:

			static void Init(LogSetting coreLogSetting, LogSetting appLogSetting);

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		private:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;
		};
	}
}

// Core Log Macros
#define MAB_CORE_TRACE(...)		::MABEngine::Logging::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MAB_CORE_INFO(...)		::MABEngine::Logging::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MAB_CORE_WARN(...)		::MABEngine::Logging::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MAB_CORE_ERROR(...)		::MABEngine::Logging::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MAB_CORE_FATAL(...)		::MABEngine::Logging::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log Macros
#define MAB_TRACE(...)			::MABEngine::Logging::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MAB_INFO(...)			::MABEngine::Logging::Log::GetClientLogger()->info(__VA_ARGS__)
#define MAB_WARN(...)			::MABEngine::Logging::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MAB_ERROR(...)			::MABEngine::Logging::Log::GetClientLogger()->error(__VA_ARGS__)
#define MAB_FATAL(...)			::MABEngine::Logging::Log::GetClientLogger()->fatal(__VA_ARGS__)
