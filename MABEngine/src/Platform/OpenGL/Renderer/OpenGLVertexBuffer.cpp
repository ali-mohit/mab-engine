#include "mabengine_pch.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace MABEngine {

	namespace Renderer {
		OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
			MAB_PROFILE_FUNCTION();

			glCreateBuffers(1, &m_RendererId);
			glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		}

		OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
			MAB_PROFILE_FUNCTION();

			glCreateBuffers(1, &m_RendererId);
			glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		}

		OpenGLVertexBuffer::~OpenGLVertexBuffer() {
			MAB_PROFILE_FUNCTION();

			glDeleteBuffers(1, &m_RendererId);
		}

		void OpenGLVertexBuffer::Bind() const
		{
			MAB_PROFILE_FUNCTION();

			glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		}

		void OpenGLVertexBuffer::UnBind() const
		{
			MAB_PROFILE_FUNCTION();

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
		}
	}
}