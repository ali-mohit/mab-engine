#pragma once

#include "MABEngine/Core.h"

namespace MABEngine {
	namespace Textures {
		
		class MABENGINE_API Texture {
		public:
			virtual ~Texture() = default;

			virtual uint32_t GetWidth() const = 0;
			virtual uint32_t GetHeight() const = 0;

			virtual void Bind(uint32_t slot = 0) = 0;
		};

	}
}