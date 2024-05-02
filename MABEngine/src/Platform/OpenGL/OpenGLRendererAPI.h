#pragma once

#include "MABEngine/Core.h"
#include "MABEngine/Renderer/RendererAPI.h"

namespace MABEngine {

	namespace Renderer {
		class MABENGINE_API OpenGLRendererAPI : public RendererAPI {
		public:
			virtual void SetClearColor(const glm::vec4& color) override;
			virtual void Clear() override;

			virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertextArray) override;
		};
	}
}
