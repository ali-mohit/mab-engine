#include "mabengine_pch.h"

#include "Platform/OpenGL/Renderer/OpenGLGraphicCardInfo.h"

#include <glad/glad.h>

namespace MABEngine {
	namespace Renderer {
		
		OpenGLGraphicCardInfo::OpenGLGraphicCardInfo(){ }
		
		OpenGLGraphicCardInfo::~OpenGLGraphicCardInfo() { }
		
		std::string OpenGLGraphicCardInfo::GetGraphicCardVendor()
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
		
		std::string OpenGLGraphicCardInfo::GetGraphicCardRenderer()
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
		
		uint32_t OpenGLGraphicCardInfo::GetMaxNumberOfTextureImageUnit()
		{
			GLint maxTextureUnit = 0;
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnit);
			return maxTextureUnit;
		}

		std::string OpenGLGraphicCardInfo::GetOpenGLVersion()
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
		
		uint32_t OpenGLGraphicCardInfo::GetMaxFrameBufferSize()
		{
			GLint maxRenderbufferSize;
			glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderbufferSize);

			return maxRenderbufferSize;
		}
	}
}