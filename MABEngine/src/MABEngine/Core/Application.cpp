#include "mabengine_pch.h"
#include "Application.h"

#include "MABEngine/Core/EngineTime.h"
#include "MABEngine/Core/Window.h"

#include "MABEngine/Logging/Log.h"
#include "MABEngine/Inputs/Input.h"
#include "MABEngine/Layers/ImGui/ImGuiLayer.h"
#include "MABEngine/Renderer/EngineRenderer.h"


#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace MABEngine {
	namespace Core {
		Application* Application::s_Instance = nullptr;

		Application::Application()
		{
			MAB_PROFILE_FUNCTION();

			ApplicationProps appProps;
			InitializeApplication(appProps);
		}

		Application::Application(const ApplicationProps& appProps)
		{
			MAB_PROFILE_FUNCTION();

			InitializeApplication(appProps);
		}

		Application::~Application()
		{
			MAB_PROFILE_FUNCTION();

			Renderer::EngineRenderer::Shutdown();
		}

		void Application::Run() {
			MAB_PROFILE_FUNCTION();

			while (m_Running) {
				MAB_PROFILE_SCOPE("Run Loop");

				float time = (float)EngineTimeObj->GetTime();
				Core::EngineTimeStep timeStep = time - m_LastFrameTime;
				m_LastFrameTime = time;

				if (!m_Minimize) {
					{
						MAB_PROFILE_SCOPE("LayerStack OnUpdate");

						for (Layers::Layer* layer : m_LayerStack)
							layer->OnUpdate(timeStep);
					}

					m_ImGuiLayer->Begin();
					{
						MAB_PROFILE_SCOPE("LayerStack OnImGuiRender");
						for (Layers::Layer* layer : m_LayerStack)
							layer->OnImGuiRender();
					}
					m_ImGuiLayer->End();
				}


				m_Window->OnUpdate();

			}
		}

		void Application::OnEvent(Events::Event& e)
		{
			MAB_PROFILE_FUNCTION();

			Events::EventDispatcher dispatcher(e);
			dispatcher.Dispatch<Events::WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
			dispatcher.Dispatch<Events::WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

			for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it ) {
				if (e.Handled)
					break;

				(*it)->OnEvent(e);
			}
		}

		void Application::PushLayer(Layers::Layer* layer)
		{
			MAB_PROFILE_FUNCTION();

			m_LayerStack.PushLayer(layer);
			layer->OnAttach();
		}

		void Application::PushOverLayer(Layers::Layer* layer)
		{
			MAB_PROFILE_FUNCTION();

			m_LayerStack.PushOverlay(layer);
			layer->OnAttach();
		}

		void Application::CloseApplication()
		{
			m_Running = false;
		}


		void Application::InitializeApplication(const ApplicationProps& appProps)
		{
			MAB_PROFILE_FUNCTION();

			MAB_CORE_ASSERT(!s_Instance, "Application already exists!");
			s_Instance = this;

			WindowProps wProp(appProps);

			m_Window = Scope<Window>(Window::Create(wProp));
			m_Window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

			Renderer::EngineRenderer::Init();

			m_ImGuiLayer = new Layers::ImGuiLayer("Debug ImGui");
			PushOverLayer(m_ImGuiLayer);

			EngineTimeObj = Scope<Core::EngineTime>(Core::EngineTime::Create());
		}

		bool Application::OnWindowClose(Events::WindowCloseEvent& e)
		{
			m_Running = false;

			return true;
		}

		bool Application::OnWindowResize(Events::WindowResizeEvent& e)
		{
			MAB_PROFILE_FUNCTION();

			if (e.GetWidth() == 0 || e.GetHeight() == 0) {
				m_Minimize = true;

				return false;
			}
			m_Minimize = false;
			Renderer::EngineRenderer::OnWindowResize(e.GetWidth(), e.GetHeight());

			return false;
		}
	}
}
