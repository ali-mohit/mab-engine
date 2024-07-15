#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/BufferLayout.h"
#include <cstdint>

namespace MABEngine {
	namespace Renderer {

		class MABENGINE_API VertexBuffer {
		public:
			virtual ~VertexBuffer() {}

			virtual void Bind() const = 0;
			virtual void UnBind() const = 0;

			virtual void SetData(const void* data, uint32_t size) = 0;

			virtual void SetLayout(const BufferLayout& layout) = 0;
			virtual const BufferLayout& GetLayout() const = 0;

			static VertexBuffer* Create(float* vertices, uint32_t size);
			static VertexBuffer* Create(uint32_t size);
		};
	}
}
