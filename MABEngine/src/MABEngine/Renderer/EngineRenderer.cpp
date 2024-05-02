#include "mabengine_pch.h"
#include "EngineRenderer.h"
#include "RenderCommand.h"

namespace MABEngine {

	namespace Renderer {

		void EngineRenderer::BeginScene()
		{
		}

		void EngineRenderer::EndScene()
		{
		}

		void EngineRenderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
		{
			vertexArray->Bind();
			RenderCommand::DrawIndexed(vertexArray);
		}

	}
}