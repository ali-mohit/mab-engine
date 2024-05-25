#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/RendererAPI.h"

namespace MABEngine {

	namespace Renderer {
		class MABENGINE_API OpenGLRendererAPI : public RendererAPI {
		public:
			virtual void Init() override;
			virtual void SetClearColor(const glm::vec4& color) override;
			virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
			virtual void Clear() override;

			virtual void DrawIndexed(const Core::Ref<VertexArray>& vertextArray) override;
		};
	}
}
