#include "mabengine_pch.h"
#include "Application.h"

#include "MABEngine/Events/ApplicationEvent.h"
#include "MABEngine/Logging/Log.h"

namespace MABEngine {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run() {
		Events::WindowResizeEvent e(100, 200);
		MAB_TRACE(e);

		while (true);
	}
}
