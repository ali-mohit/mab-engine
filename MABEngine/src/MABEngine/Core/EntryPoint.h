#pragma once

#ifdef MABENGINE_PLATFORM_WINDOWS

#include "MABEngine/Core/Application.h"
#include "MABEngine/Core/Settings.h"
#include "MABEngine/Logging/Log.h"

extern MABEngine::Core::Application* MABEngine::Core::CreateApplication(int argc, char** argv);

int main(int argc, char** argv) {
	
	auto appSetting = MABEngine::Core::Setting();
	MABEngine::Logging::Log::Init(appSetting.GetCoreLogSettings(), appSetting.GetAppLogSettings());


	MAB_PROFILE_BEGIN_SESSION("Startup", "MABEngine-Profiler-Startup.json");
	auto app = MABEngine::Core::CreateApplication(argc, argv);
	MAB_PROFILE_END_SESSION();


	MAB_PROFILE_BEGIN_SESSION("Startup", "MABEngine-Profiler-Runtime.json");
	app->Run();
	MAB_PROFILE_END_SESSION();


	MAB_PROFILE_BEGIN_SESSION("Startup", "MABEngine-Profiler-Shutdown.json");
	delete app;
	MAB_PROFILE_END_SESSION();

	return 0;
}

#endif
