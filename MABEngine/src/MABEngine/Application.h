#pragma once

#include "Core.h"

#include "Window.h"
#include "MABEngine/Layers/LayerStack.h"
#include "MABEngine/Events/Event.h"
#include "MABEngine/Events/ApplicationEvent.h"


namespace MABEngine {
	class MABENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();

		void OnEvent(Events::Event& e);
		void PushLayer(Layers::Layer* layer);
		void PushOverLayer(Layers::Layer* layer);
	private:
		bool OnWindowClose(Events::WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		Layers::LayerStack m_LayerStack;
	};

	// To be defined in Projects that want to use MABEngine
	Application* CreateApplication(int argc, char** argv);
}