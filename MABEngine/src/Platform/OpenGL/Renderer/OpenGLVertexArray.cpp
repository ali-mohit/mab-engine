#include "mabengine_pch.h"
#include "MABEngine/Core/Base.h"
#include "OpenGLVertexArray.h"
#include "OpenGLEngineRenderer.h"

#include <glad/glad.h>

namespace MABEngine {

	namespace Renderer {
		OpenGLVertexArray::OpenGLVertexArray()
		{
			MAB_PROFILE_FUNCTION();

			glCreateVertexArrays(1, &m_RendererId);
		}
		
		OpenGLVertexArray::~OpenGLVertexArray()
		{
			MAB_PROFILE_FUNCTION();

			glDeleteVertexArrays(1, &m_RendererId);
		}

		void OpenGLVertexArray::Bind() const
		{
			MAB_PROFILE_FUNCTION();

			glBindVertexArray(m_RendererId);
		}

		void OpenGLVertexArray::UnBind() const
		{
			MAB_PROFILE_FUNCTION();

			glBindVertexArray(0);
		}
		
		void OpenGLVertexArray::AddVertexBuffer(const Core::Ref<VertexBuffer>& vertexBuffer)
		{
			MAB_PROFILE_FUNCTION();

			MAB_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

			glBindVertexArray(m_RendererId);
			vertexBuffer->Bind();

			uint32_t index = 0;
			const auto& layout = vertexBuffer->GetLayout();
			for (const auto& element : layout) {
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(
					index,
					element.GetComponentCount(),
					ShaderDataTypToOpenGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset);
				index++;
			}

			m_VertexBufferList.push_back(vertexBuffer);
		}
		
		void OpenGLVertexArray::SetIndexBuffer(const Core::Ref<IndexBuffer>& indexBuffer)
		{
			MAB_PROFILE_FUNCTION();

			glBindVertexArray(m_RendererId);
			indexBuffer->Bind();

			m_IndexBuffer = indexBuffer;
		}
	}

}