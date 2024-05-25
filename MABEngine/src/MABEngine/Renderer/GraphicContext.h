#pragma once

#include "MABEngine/Core/Base.h"

namespace MABEngine {
	namespace Renderer {
		class MABENGINE_API GraphicContext {
		public:
			virtual void Init() = 0;
			virtual void SwapBuffers() = 0;

			virtual std::string GetGraphicCardVendor() = 0;
			virtual std::string GetGraphicCardRenderer() = 0;
			virtual uint32_t GetMaxNumberOfTextureImageUnit() = 0;
		};
	}
}