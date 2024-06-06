#include "mabengine_pch.h"
#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace MABEngine {

	namespace Renderer {
		OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
			:m_Count(count)
		{
			MAB_PROFILE_FUNCTION();

			glCreateBuffers(1, &m_RendererId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		}

		OpenGLIndexBuffer::~OpenGLIndexBuffer() {
			MAB_PROFILE_FUNCTION();

			glDeleteBuffers(1, &m_RendererId);
		}

		void OpenGLIndexBuffer::Bind() const {
			MAB_PROFILE_FUNCTION();

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
		}
		
		void OpenGLIndexBuffer::UnBind() const {
			MAB_PROFILE_FUNCTION();

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}