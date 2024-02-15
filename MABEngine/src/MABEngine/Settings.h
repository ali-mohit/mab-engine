#pragma once

#include <string.h>

#include "spdlog/spdlog.h"

#include "Core.h"
#include "Logging/LogSetting.h"

namespace MABEngine {
	class MABENGINE_API Setting {
	public:
		Setting() :
			mCoreLogSetting("MAB ENGINE", Logging::trace),
			mAppLogSetting("APP", Logging::trace) {}

		Setting(Logging::LogSetting coreLogSetting, Logging::LogSetting appLogSetting) :
			mCoreLogSetting(coreLogSetting),
			mAppLogSetting(appLogSetting) {}
			
		inline Logging::LogSetting& GetCoreLogSettings() { return mCoreLogSetting; }
		inline Logging::LogSetting& GetAppLogSettings() { return mAppLogSetting; }
	private:
		Logging::LogSetting mCoreLogSetting;
		Logging::LogSetting mAppLogSetting;
	};
}


