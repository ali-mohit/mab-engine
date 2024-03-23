#include "mabengine_pch.h"
#include "Application.h"

#include "MABEngine/Events/ApplicationEvent.h"
#include "MABEngine/Logging/Log.h"

namespace MABEngine {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run() {
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
}
