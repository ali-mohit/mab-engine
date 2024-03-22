#pragma once

#ifdef MABENGINE_PLATFORM_WINDOWS

#include "Application.h"

extern MABEngine::Application* MABEngine::CreateApplication(int argc, char** argv);

int main(int argc, char** argv) {
	
	auto appSetting = MABEngine::Setting();
	MABEngine::Logging::Log::Init(appSetting.GetCoreLogSettings(), appSetting.GetAppLogSettings());

	auto app = MABEngine::CreateApplication(argc, argv);

	app->Run();

	delete app;

	return 0;
}

#endif
