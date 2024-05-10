#pragma once

#include <glm/glm.hpp>

#include "MABEngine/Core.h"
#include "MABEngine/Renderer/RenderAPIType.h"
#include "MABEngine/Renderer/VertexArray.h"

namespace MABEngine {

	namespace Renderer {

		class MABENGINE_API RendererAPI {
		public:
			virtual void SetClearColor(const glm::vec4& color) = 0;
			virtual void Clear() = 0;

			virtual void DrawIndexed(const Ref<VertexArray>& vertextArray) = 0;

			inline static RendererAPIType GetAPI() { return s_APIType; }
		private:
			static RendererAPIType s_APIType;
		};

	}
}