#include "mabengine_pch.h"
#include "GLFW/glfw3.h"

#include "WindowsGlfwInput.h"
#include "MABEngine/Application.h"

namespace MABEngine {
	namespace Inputs {

		Input* Input::s_Instance = new WindowsGlfwInput();

		bool WindowsGlfwInput::IsKeyPressedImp(MABKeyboardCode keyCode)
		{
			auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
			auto state = glfwGetKey(window, (int)keyCode);

			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

		bool WindowsGlfwInput::IsKeyRepeatImp(MABKeyboardCode keyCode)
		{
			auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
			auto state = glfwGetKey(window, (int)keyCode);

			return state == GLFW_REPEAT;
		}

		bool WindowsGlfwInput::IsMouseButtonPressedImp(MABMouseButton buttonCode)
		{
			auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
			auto state = glfwGetMouseButton(window, (int)buttonCode);

			return state == GLFW_PRESS;
		}

		std::pair<double, double> WindowsGlfwInput::GetMousePosImp()
		{
			auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
			
			double xPos;
			double yPos;
			glfwGetCursorPos(window, &xPos, &yPos);

			return { xPos, yPos };
		}

		double WindowsGlfwInput::GetMousePosXImp()
		{
			auto[x,y] = GetMousePosImp();
			return x;
		}

		double WindowsGlfwInput::GetMousePosYImp()
		{
			auto[x, y] = GetMousePosImp();
			return y;
		}

	}
}