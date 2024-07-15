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

			inline static uint32_t GetMaxNumberOfTextureImageUnit() {
				return s_RendererAPI->GetMaxNumberOfTextureImageUnit();
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

			inline static void DrawIndexed(const Core::Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) {
				s_RendererAPI->DrawIndexed(vertexArray, indexCount);
			}
		private:
			static RendererAPI* s_RendererAPI;
		};
	}
}
