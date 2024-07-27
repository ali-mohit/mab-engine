#include "mabengine_pch.h"
#include "GLFW/glfw3.h"

#include "MABEngine/Core/Application.h"
#include "MABEngine/Inputs/Input.h"

namespace MABEngine {
	namespace Inputs {

		bool Input::IsKeyPressed(MABKeyboardCode keyCode)
		{
			auto window = static_cast<GLFWwindow*>(Core::Application::Get().GetWindow().GetNativeWindow());
			auto state = glfwGetKey(window, (int)keyCode);

			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

		bool Input::IsKeyRepeat(MABKeyboardCode keyCode)
		{
			auto window = static_cast<GLFWwindow*>(Core::Application::Get().GetWindow().GetNativeWindow());
			auto state = glfwGetKey(window, (int)keyCode);

			return state == GLFW_REPEAT;
		}

		bool Input::IsMouseButtonPressed(MABMouseButton buttonCode)
		{
			auto window = static_cast<GLFWwindow*>(Core::Application::Get().GetWindow().GetNativeWindow());
			auto state = glfwGetMouseButton(window, (int)buttonCode);

			return state == GLFW_PRESS;
		}

		std::pair<double, double> Input::GetMousePos()
		{
			auto window = static_cast<GLFWwindow*>(Core::Application::Get().GetWindow().GetNativeWindow());
			
			double xPos;
			double yPos;
			glfwGetCursorPos(window, &xPos, &yPos);

			return { xPos, yPos };
		}

		double Input::GetMousePosX()
		{
			auto[x,y] = GetMousePos();
			return x;
		}

		double Input::GetMousePosY()
		{
			auto[x, y] = GetMousePos();
			return y;
		}
	}
}