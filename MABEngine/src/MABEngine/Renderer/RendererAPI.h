#pragma once

#include <glm/glm.hpp>

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/RenderAPIType.h"
#include "MABEngine/Renderer/VertexArray.h"
#include "MABEngine/Renderer/SceneDataType.h"

namespace MABEngine {

	namespace Renderer {

		class MABENGINE_API RendererAPI {
		public:
			virtual ~RendererAPI() = default;

			virtual void Init() = 0;

			virtual uint32_t GetMaxNumberOfTextureImageUnit() = 0;
			virtual uint32_t GetMaxFrameBufferSize() = 0;
			virtual void SetClearColor(const glm::vec4& color) = 0;
			virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
			virtual void SetPipelineConfig(const PipelineConfig& pipelineConfig) = 0;

			virtual void Clear() = 0;

			virtual void DrawIndexed(const Core::Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
			virtual void DrawLines(const Core::Ref<VertexArray>& vertexArray, uint32_t vertexCount = 0) = 0;

			inline static RendererAPIType GetAPI() { return s_APIType; }
		private:
			static RendererAPIType s_APIType;
		};

	}
}