#include "mabengine_pch.h"
#include "WindowsGlfwWindow.h"

#include "MABEngine/Core.h"
#include "MABEngine/Logging/Log.h"


namespace MABEngine {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) {
		return new WindowsGlfwWindow(props);
	}

	WindowsGlfwWindow::WindowsGlfwWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsGlfwWindow::~WindowsGlfwWindow() {
		Shutdown();
	}

	void WindowsGlfwWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		MAB_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			MAB_CORE_ASSERT(success, "Could not initialize GLFW");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsGlfwWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsGlfwWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsGlfwWindow::SetVSync(bool enabled) {
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
