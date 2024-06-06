#include "mabengine_pch.h"

#include "MABEngine/Core/Base.h"
#include "Platform/OpenGL/Renderer/OpenGLGraphicContext.h"
#include "MABEngine/Logging/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace MABEngine {
	namespace Renderer {
		OpenGLGraphicContext::OpenGLGraphicContext(GLFWwindow* windowHandle)
			:m_WindowHandle(windowHandle) 
		{
			MAB_CORE_ASSERT(m_WindowHandle, "Windows Handler is null!");
		}

		void OpenGLGraphicContext::Init() {
			MAB_PROFILE_FUNCTION();

			glfwMakeContextCurrent(m_WindowHandle);

			int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			MAB_CORE_ASSERT(status, "Failed to initialize GLAD (OpenGL)!");

			MAB_CORE_INFO("OPENGL info:");
			MAB_CORE_INFO(" Vendor:			{0}", GetGraphicCardVendor());
			MAB_CORE_INFO(" Renderer:		{0}", GetGraphicCardRenderer());
			MAB_CORE_INFO(" Version:		{0}", GetOpenGLVersion());
			MAB_CORE_INFO(" No. of Texture Units:	{0}", std::to_string(GetMaxNumberOfTextureImageUnit()).c_str());

			MAB_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "MAB Engine requires at least OpenGL version 4.5!");
		}

		void OpenGLGraphicContext::SwapBuffers() {
			MAB_PROFILE_FUNCTION();

			glfwSwapBuffers(m_WindowHandle);
		}

		std::string OpenGLGraphicContext::GetGraphicCardVendor()
		{
			if (m_GraphicCardVendor.empty()) {
				const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
				if (vendor) {
					m_GraphicCardVendor = std::string(vendor);
				}
				else {
					m_GraphicCardVendor = "";
				}
			}
			
			return m_GraphicCardVendor;
		}

		std::string OpenGLGraphicContext::GetGraphicCardRenderer()
		{
			if (m_GraphicCardRenderer.empty()) {
				const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
				if (renderer) {
					m_GraphicCardRenderer = std::string(renderer);
				}
				else {
					m_GraphicCardRenderer = "";
				}
			}

			return m_GraphicCardRenderer;
		}

		uint32_t OpenGLGraphicContext::GetMaxNumberOfTextureImageUnit()
		{
			GLint maxTextureUnit = 0;
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnit);
			return maxTextureUnit;
		}

		std::string OpenGLGraphicContext::GetOpenGLVersion()
		{
			if (m_OpenGLVersion.empty()) {
				const char* openGlVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
				if (openGlVersion) {
					m_OpenGLVersion = std::string(openGlVersion);
				}
				else {
					m_OpenGLVersion = "";
				}
			}

			return m_OpenGLVersion;
		}

	}
}