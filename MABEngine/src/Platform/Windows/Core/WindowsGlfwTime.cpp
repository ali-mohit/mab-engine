#include "mabengine_pch.h"
#include "WindowsGlfwTime.h"

#include "GLFW/glfw3.h"

namespace MABEngine {
	namespace Core {

		double GlfwTime::GetTime()
		{
			return glfwGetTime();
		}

	}
}