#include "mabengine_pch.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace MABEngine {

	namespace Renderer {
		OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
		{
			glCreateBuffers(1, &m_RendererId);
			glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		}

		OpenGLVertexBuffer::~OpenGLVertexBuffer() {
			glDeleteBuffers(1, &m_RendererId);
		}

		void OpenGLVertexBuffer::Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		}

		void OpenGLVertexBuffer::UnBind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}