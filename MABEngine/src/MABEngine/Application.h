#pragma once

#include "Core.h"
#include "MABEngine/Events/Event.h"
#include "MABEngine/Events/ApplicationEvent.h"
#include "Window.h"

namespace MABEngine {
	class MABENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();

		void OnEvent(Events::Event& e);
	private:
		bool OnWindowClose(Events::WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in Projects that want to use MABEngine
	Application* CreateApplication(int argc, char** argv);
}