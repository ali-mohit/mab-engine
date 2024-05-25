#pragma once

#include "MABEngine/Renderer/IndexBuffer.h"
#include "MABEngine/Core/Base.h"

namespace MABEngine {
	namespace Renderer {

		class MABENGINE_API OpenGLIndexBuffer : public IndexBuffer {
		public:
			OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
			virtual ~OpenGLIndexBuffer();

			virtual void Bind() const override;
			virtual void UnBind() const override;
			
			inline virtual uint32_t GetCount() const { return m_Count; };
		private:
			uint32_t m_RendererId;
			uint32_t m_Count;
		};

	}
}
