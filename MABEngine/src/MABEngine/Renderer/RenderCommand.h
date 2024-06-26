#pragma once
#include <glm/glm.hpp>

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/RenderAPIType.h"
#include "MABEngine/Renderer/RendererAPI.h"

namespace MABEngine {

	namespace Renderer {
		class MABENGINE_API RenderCommand {
		public:
			inline static void Init() {
				s_RendererAPI->Init();
			}

			inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
				s_RendererAPI->SetViewport(x, y, width, height);
			}

			inline static void SetClearColor(const glm::vec4& color) {
				s_RendererAPI->SetClearColor(color);
			}

			inline static void Clear() {
				s_RendererAPI->Clear();
			}

			inline static void DrawIndexed(const Core::Ref<VertexArray>& vertexArray) {
				s_RendererAPI->DrawIndexed(vertexArray);
			}
		private:
			static RendererAPI* s_RendererAPI;
		};
	}
}
