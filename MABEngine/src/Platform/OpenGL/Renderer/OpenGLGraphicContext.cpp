#include "mabengine_pch.h"

#include "MABEngine/Core/Base.h"
#include "Platform/OpenGL/Renderer/OpenGLGraphicContext.h"
#include "MABEngine/Logging/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace MABEngine {
	namespace Renderer {
		OpenGLGraphicContext::OpenGLGraphicContext(GLFWwindow* windowHandle, Core::Ref<GraphicCardInfo> graphicCardInfo)
			:m_WindowHandle(windowHandle), m_GraphicCardInfo(graphicCardInfo)
		{
			MAB_CORE_ASSERT(m_WindowHandle, "Windows Handler is null!");
		}

		void OpenGLGraphicContext::Init() {
			MAB_PROFILE_FUNCTION();

			glfwMakeContextCurrent(m_WindowHandle);

			int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			MAB_CORE_ASSERT(status, "Failed to initialize GLAD (OpenGL)!");

			MAB_CORE_INFO("OPENGL info:");
			MAB_CORE_INFO(" Vendor:			{0}", m_GraphicCardInfo->GetGraphicCardVendor());
			MAB_CORE_INFO(" Renderer:		{0}", m_GraphicCardInfo->GetGraphicCardRenderer());
			MAB_CORE_INFO(" Version:		{0}", m_GraphicCardInfo->GetOpenGLVersion());
			MAB_CORE_INFO(" No. of Texture Units:	{0}", std::to_string(m_GraphicCardInfo->GetMaxNumberOfTextureImageUnit()).c_str());

			MAB_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "MAB Engine requires at least OpenGL version 4.5!");
		}

		void OpenGLGraphicContext::SwapBuffers() {
			MAB_PROFILE_FUNCTION();

			glfwSwapBuffers(m_WindowHandle);
		}

	}
}