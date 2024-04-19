#pragma once

#include "MABEngine/Core.h"
#include <cstdint>

namespace MABEngine {
	namespace Renderer {

		class MABENGINE_API VertexBuffer {
		public:
			virtual ~VertexBuffer() {}

			virtual void Bind() const = 0;
			virtual void UnBind() const = 0;

			static VertexBuffer* Create(float* vertices, uint32_t size);
		};
	}
}
