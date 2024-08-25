#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/RendererAPI.h"

namespace MABEngine {

	namespace Renderer {
		class MABENGINE_API OpenGLRendererAPI : public RendererAPI {
		public:
			virtual void Init() override;

			virtual uint32_t GetMaxNumberOfTextureImageUnit() override;
			virtual uint32_t GetMaxFrameBufferSize() override;

			virtual void SetClearColor(const glm::vec4& color) override;
			virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
			virtual void Clear() override;
			virtual void SetPipelineConfig(const PipelineConfig& pipelineConfig) override;

			virtual void DrawIndexed(const Core::Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
			virtual void DrawLines(const Core::Ref<VertexArray>& vertextArray, uint32_t vertexCount = 0) override;
		};
	}
}
