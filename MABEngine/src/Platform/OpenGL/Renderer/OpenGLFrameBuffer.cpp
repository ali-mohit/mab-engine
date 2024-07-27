#include "mabengine_pch.h"
#include "Platform/OpenGL/Renderer/OpenGLFrameBuffer.h"

#include <glad/glad.h>

namespace MABEngine {

	namespace Renderer {
		
		OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec)
			:m_Specification(spec)
		{
			RebuildFrameBuffer();
		}
		
		OpenGLFrameBuffer::~OpenGLFrameBuffer()
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachmentID);
			glDeleteTextures(1, &m_DepthAttachmentID);
		}

		void OpenGLFrameBuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
			glViewport(0, 0, m_Specification.Width, m_Specification.Height);
		}

		void OpenGLFrameBuffer::UnBind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
		{
			m_Specification.Width = width;
			m_Specification.Height = height;

			RebuildFrameBuffer();
		}

		void OpenGLFrameBuffer::RebuildFrameBuffer()
		{
			if (m_RendererID > 0) {
				glDeleteFramebuffers(1, &m_RendererID);
				glDeleteTextures(1, &m_ColorAttachmentID);

				if(m_DepthAttachmentID > 0)
					glDeleteTextures(1, &m_DepthAttachmentID);
			}

			//Create FrameBuffer
			glGenFramebuffers(1, &m_RendererID);
			glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
			
			//Create Texture and attach texture to framebuffer
			glGenTextures(1, &m_ColorAttachmentID);
			glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentID);

			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RGBA8,
				m_Specification.Width,
				m_Specification.Height,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				0
			);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glFramebufferTexture2D(
				GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0,
				GL_TEXTURE_2D,
				m_ColorAttachmentID,
				0
			);

			// Create and attach depth buffer if needed
			if (m_Specification.ActivateDepthBuffer) {
				
				glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachmentID);
				glBindTexture(GL_TEXTURE_2D, m_DepthAttachmentID);
				glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachmentID, 0);

			}

			MAB_CORE_ASSERT(
				glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
				"Frame Buffer is incomplete"
			);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}