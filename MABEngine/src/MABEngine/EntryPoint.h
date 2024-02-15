#pragma once

#ifdef MABENGINE_PLATFORM_WINDOWS

#include "Application.h"

extern MABEngine::Application* MABEngine::CreateApplication(int argc, char** argv);

int main(int argc, char** argv) {
	
	auto appSetting = MABEngine::Setting();
	MABEngine::Logging::Log::Init(appSetting.GetCoreLogSettings(), appSetting.GetAppLogSettings());

	MAB_CORE_WARN("HELLO WORD core logger");

	int a = 5;
	MAB_INFO("HELLO WORD app logger var={0}", a);

	auto app = MABEngine::CreateApplication(argc, argv);

	app->Run();

	delete app;

	return 0;
}

#endif
