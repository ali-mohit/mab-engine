#pragma once

#include "MABEngine/Core/Base.h"
#include <cstdint>

namespace MABEngine {
	namespace Renderer {

		class MABENGINE_API IndexBuffer {
		public:
			virtual ~IndexBuffer() {}

			virtual void Bind() const = 0;
			virtual void UnBind() const = 0;

			virtual void SetData(const void* data, uint32_t size) = 0;

			virtual uint32_t GetCount() const = 0;

			static IndexBuffer* Create(uint32_t* indices, uint32_t count);
			static IndexBuffer* Create(uint32_t size, uint32_t elementSize = sizeof(uint32_t));
		};
	}
}
