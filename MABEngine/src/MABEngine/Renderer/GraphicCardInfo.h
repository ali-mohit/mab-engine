#pragma once

#include "MABEngine/Core/Base.h"

#include <string>

namespace MABEngine {
	namespace Renderer {

		class MABENGINE_API GraphicCardInfo {
		public:
			~GraphicCardInfo() = default;

			virtual std::string GetGraphicCardVendor() = 0;
			virtual std::string GetGraphicCardRenderer() = 0;
			virtual uint32_t GetMaxNumberOfTextureImageUnit() = 0;
			virtual uint32_t GetMaxFrameBufferSize() = 0;
			virtual std::string GetOpenGLVersion() = 0;

			static Core::Ref<GraphicCardInfo> Create();
		};

	}
}