#include "mabengine_pch.h"

#include "WindowsGlfwWindow.h"
#include "Platform/OpenGL/Renderer/OpenGLGraphicContext.h"

#include "MABEngine/Core/Base.h"
#include "MABEngine/Logging/Log.h"

#include "MABEngine/Events/Event.h"
#include "MABEngine/Events/ApplicationEvent.h"
#include "MABEngine/Events/KeyEvent.h"
#include "MABEngine/Events/MouseEvent.h"
#include "MABEngine/Inputs/KeyboardCodes.h"
#include "MABEngine/Inputs/MouseButtonCodes.h"

#include "MABEngine/Renderer/GraphicCardInfo.h"

#include <GLFW/glfw3.h>


namespace MABEngine {
	namespace Core {
		static uint32_t s_GLFWWindowCount = 0;

		static void GLFWErrorCallBack(int error, const char* description) {
			MAB_CORE_ERROR("GLFW Error CallBack: (code: {0} - text: {1})", error, description);
		}

		Scope<Window> Window::Create(const WindowProps& props) {
			return CreateScope<WindowsGlfwWindow>(props);
		}

		WindowsGlfwWindow::WindowsGlfwWindow(const WindowProps& props) {
			MAB_PROFILE_FUNCTION();

			Init(props);
		}

		WindowsGlfwWindow::~WindowsGlfwWindow() {
			MAB_PROFILE_FUNCTION();

			Shutdown();
		}

		void WindowsGlfwWindow::Init(const WindowProps& props) {
			MAB_PROFILE_FUNCTION();

			m_Data.Title = props.Title;
			m_Data.Width = props.Width;
			m_Data.Height = props.Height;

			MAB_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

			if (s_GLFWWindowCount == 0) {
				MAB_PROFILE_SCOPE("glfwInit");

				int success = glfwInit();
				MAB_CORE_ASSERT(success, "Could not initialize GLFW");
				glfwSetErrorCallback(GLFWErrorCallBack);
			}

			{
				MAB_PROFILE_SCOPE("glfwCreateWindow");

				m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
				s_GLFWWindowCount++;
			}

			m_GraphicCardInfo = Renderer::GraphicCardInfo::Create();

			m_GraphicContext = new Renderer::OpenGLGraphicContext(m_Window, m_GraphicCardInfo);
			m_GraphicContext->Init();

			glfwSetWindowUserPointer(m_Window, &m_Data);
			SetVSync(true);

			//Set GLFW callbacks
			glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
					data.Width = width;
					data.Height = height;

					Events::WindowResizeEvent event(width, height);
					data.EventCallBack(event);

				}
			);

			glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

					Events::WindowCloseEvent event;
					data.EventCallBack(event);
				}
			);

			glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

					if (focused == GLFW_TRUE) {
						Events::WindowFocusEvent event(focused);
						data.EventCallBack(event);
					}
					else
					{
						Events::WindowLossFocusEvent event(focused);
						data.EventCallBack(event);

					}
				}
			);

			glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xpos, int ypos)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

					Events::WindowMovedEvent e(xpos, ypos);
					data.EventCallBack(e);
				}
			);

			glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scanCode, int action, int modes) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					Events::KeyPressedEvent e(static_cast<Inputs::MABKeyboardCode>(key), 0);
					data.EventCallBack(e);
					break;
				}
				case GLFW_RELEASE:
				{
					Events::KeyReleasedEvent e(static_cast<Inputs::MABKeyboardCode>(key));
					data.EventCallBack(e);
					break;
				}
				case GLFW_REPEAT:
				{
					Events::KeyPressedEvent e(static_cast<Inputs::MABKeyboardCode>(key), 1);
					data.EventCallBack(e);
					break;
				}
				}
				}
			);

			glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
					switch (action)
					{
					case GLFW_PRESS:
					{
						Events::MouseButtonPressedEvent e(static_cast<Inputs::MABMouseButton>(button));
						data.EventCallBack(e);
						break;
					}
					case GLFW_RELEASE:
					{
						Events::MouseButtonReleasedEvent e(static_cast<Inputs::MABMouseButton>(button));
						data.EventCallBack(e);
						break;
					}
					}
				}
			);

			glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

					Events::MouseScrolledEvent event(xOffset, yOffset);
					data.EventCallBack(event);
				}
			);

			glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

					Events::MouseMovedEvent event((float)xPos, (float)yPos);
					data.EventCallBack(event);
				}
			);

		}

		void WindowsGlfwWindow::Shutdown() {
			MAB_PROFILE_FUNCTION();

			glfwDestroyWindow(m_Window);

			s_GLFWWindowCount--;
			if (s_GLFWWindowCount == 0) {
				glfwTerminate();
			}
		}

		void WindowsGlfwWindow::OnUpdate() {
			MAB_PROFILE_FUNCTION();

			glfwPollEvents();
			m_GraphicContext->SwapBuffers();
		}

		void WindowsGlfwWindow::SetVSync(bool enabled) {
			MAB_PROFILE_FUNCTION();

			if (enabled)
				glfwSwapInterval(1);
			else
				glfwSwapInterval(0);

			m_Data.VSync = enabled;
		}

		bool WindowsGlfwWindow::IsVSync() const {
			return m_Data.VSync;
		}
	}
}
