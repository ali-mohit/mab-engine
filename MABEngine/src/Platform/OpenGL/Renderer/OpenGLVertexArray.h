#pragma once

#include "MABEngine/Core/Base.h"
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

			virtual void AddVertexBuffer(const Core::Ref<VertexBuffer>& vertexBuffer) override;
			virtual void SetIndexBuffer(const Core::Ref<IndexBuffer>& indexBuffer) override;

			virtual const std::vector<Core::Ref<VertexBuffer>>& GetVertexBufferList() const override { return m_VertexBufferList; }
			virtual const Core::Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
		private:
			uint32_t m_RendererId;
			std::vector<Core::Ref<VertexBuffer>> m_VertexBufferList;
			Core::Ref<IndexBuffer> m_IndexBuffer;
		};
	}
}


