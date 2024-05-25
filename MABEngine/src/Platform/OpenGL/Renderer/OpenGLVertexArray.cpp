#include "mabengine_pch.h"
#include "MABEngine/Core/Base.h"
#include "OpenGLVertexArray.h"
#include "OpenGLEngineRenderer.h"

#include <glad/glad.h>

namespace MABEngine {

	namespace Renderer {
		OpenGLVertexArray::OpenGLVertexArray()
		{
			glCreateVertexArrays(1, &m_RendererId);
		}
		
		OpenGLVertexArray::~OpenGLVertexArray()
		{
			glDeleteVertexArrays(1, &m_RendererId);
		}

		void OpenGLVertexArray::Bind() const
		{
			glBindVertexArray(m_RendererId);
		}

		void OpenGLVertexArray::UnBind() const
		{
			glBindVertexArray(0);
		}
		
		void OpenGLVertexArray::AddVertexBuffer(const Core::Ref<VertexBuffer>& vertexBuffer)
		{
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
		
		void OpenGLVertexArray::AddIndexBuffer(const Core::Ref<IndexBuffer>& indexBuffer)
		{
			glBindVertexArray(m_RendererId);
			indexBuffer->Bind();

			m_IndexBufferList.push_back(indexBuffer);
		}
	}

}