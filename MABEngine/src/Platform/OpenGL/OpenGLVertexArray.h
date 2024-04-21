#pragma once

#include "MABEngine/Core.h"
#include "MABEngine/Renderer/VertexArray.h"
#include "MABEngine/Renderer/VertexBuffer.h"
#include "MABEngine/Renderer/IndexBuffer.h"

namespace MABEngine {
	namespace Renderer {
		class MABENGINE_API OpenGLVertexArray: public VertexArray
		{
		public:
			OpenGLVertexArray();
			~OpenGLVertexArray();

			virtual void Bind() const override;
			virtual void UnBind() const override;

			virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
			virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

			virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBufferList() const override { return m_VertexBufferList; }
			virtual const std::vector<std::shared_ptr<IndexBuffer>>& GetIndexBufferList() const override { return m_IndexBufferList; }
		private:
			uint32_t m_RendererId;
			std::vector<std::shared_ptr<VertexBuffer>> m_VertexBufferList;
			std::vector<std::shared_ptr<IndexBuffer>> m_IndexBufferList;
		};
	}
}


