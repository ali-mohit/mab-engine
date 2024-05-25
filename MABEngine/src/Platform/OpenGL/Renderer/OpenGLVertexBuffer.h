#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/VertexBuffer.h"
#include "MABEngine/Renderer/BufferLayout.h"


namespace MABEngine {
	namespace Renderer {

		class MABENGINE_API OpenGLVertexBuffer : public VertexBuffer {
		public:
			OpenGLVertexBuffer(float* vertices, uint32_t size);
			virtual ~OpenGLVertexBuffer();

			virtual void Bind() const override;
			virtual void UnBind() const override;

			virtual void SetLayout(const BufferLayout& layout) { m_Layout = layout; };
			virtual const BufferLayout& GetLayout() const override { return m_Layout; }

		private:
			uint32_t m_RendererId;
			BufferLayout m_Layout;

		};

	}
}