#pragma once

#ifdef MABENGINE_PLATFORM_WINDOWS

#include "MABEngine/Core/Application.h"
#include "MABEngine/Core/Settings.h"
#include "MABEngine/Logging/Log.h"

extern MABEngine::Core::Application* MABEngine::Core::CreateApplication(int argc, char** argv);

int main(int argc, char** argv) {
	
	auto appSetting = MABEngine::Core::Setting();
	MABEngine::Logging::Log::Init(appSetting.GetCoreLogSettings(), appSetting.GetAppLogSettings());

	auto app = MABEngine::Core::CreateApplication(argc, argv);

	app->Run();

	delete app;

	return 0;
}

#endif
