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
		}

		void OpenGLFrameBuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		}

		void OpenGLFrameBuffer::UnBind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void OpenGLFrameBuffer::RebuildFrameBuffer()
		{
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
				
				/*glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachmentID);
				glBindTexture(GL_TEXTURE_2D, m_DepthAttachmentID);
				glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachmentID, 0);*/

				glGenRenderbuffers(1, &m_DepthAttachmentID);
				glBindRenderbuffer(GL_RENDERBUFFER, m_DepthAttachmentID);

				glRenderbufferStorage(
					GL_RENDERBUFFER,
					GL_DEPTH24_STENCIL8,
					m_Specification.Width,
					m_Specification.Height
				);

				glFramebufferRenderbuffer(
					GL_FRAMEBUFFER,
					GL_DEPTH_ATTACHMENT,
					GL_RENDERBUFFER,
					m_DepthAttachmentID
				);
			}

			MAB_CORE_ASSERT(
				glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
				"Frame Buffer is incomplete"
			);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}