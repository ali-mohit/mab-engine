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

			virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
			virtual void AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

			virtual const std::vector<Ref<VertexBuffer>>& GetVertexBufferList() const override { return m_VertexBufferList; }
			virtual const std::vector<Ref<IndexBuffer>>& GetIndexBufferList() const override { return m_IndexBufferList; }
		private:
			uint32_t m_RendererId;
			std::vector<Ref<VertexBuffer>> m_VertexBufferList;
			std::vector<Ref<IndexBuffer>> m_IndexBufferList;
		};
	}
}


