#pragma once

#include "MABEngine/Renderer/VertexBuffer.h"
#include "MABEngine/Core.h"

namespace MABEngine {
	namespace Renderer {

		class MABENGINE_API OpenGLVertexBuffer : public VertexBuffer {
		public:
			OpenGLVertexBuffer(float* vertices, uint32_t size);
			virtual ~OpenGLVertexBuffer();

			virtual void Bind() const;
			virtual void UnBind() const;
		private:
			uint32_t m_RendererId;
		};

	}
}