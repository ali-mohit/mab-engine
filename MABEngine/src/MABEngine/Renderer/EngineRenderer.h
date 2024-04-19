#pragma once

#include "MABEngine/Core.h"

namespace MABEngine {

	namespace Renderer {

		enum class RendererAPIType {
			None = 0,
			OpenGL = 10,
		};

		class MABENGINE_API EngineRenderer
		{
		public:
			inline static RendererAPIType GetCurrentAPI() { return s_RendererAPI; }
		private:
			static RendererAPIType s_RendererAPI;
		};

	}
}


