#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/GraphicCardInfo.h"

namespace MABEngine {
	namespace Renderer {
		class MABENGINE_API GraphicContext {
		public:
			virtual ~GraphicContext() = default;

			virtual void Init() = 0;
			virtual void SwapBuffers() = 0;

			virtual const Core::Ref<GraphicCardInfo> GetGraphicCardInfo() const = 0;
		};
	}
}