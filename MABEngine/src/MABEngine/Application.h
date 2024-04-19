#pragma once

#include "Core.h"

#include "Window.h"
#include "MABEngine/Layers/LayerStack.h"
#include "MABEngine/Layers/ImGui/ImGuiLayer.h"
#include "MABEngine/Events/Event.h"
#include "MABEngine/Events/ApplicationEvent.h"

#include "MABEngine/Renderer/Shader.h"
#include "MABEngine/Renderer/VertexBuffer.h"
#include "MABEngine/Renderer/IndexBuffer.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(Events::WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		Layers::ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		Layers::LayerStack m_LayerStack;

		std::unique_ptr<Renderer::Shader> m_Shader;
		std::unique_ptr<Renderer::VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Renderer::IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;

		unsigned int m_VertexArray;
	};

	// To be defined in Projects that want to use MABEngine
	Application* CreateApplication(int argc, char** argv);
}