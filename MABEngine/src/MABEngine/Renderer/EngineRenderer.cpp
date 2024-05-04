#include "mabengine_pch.h"
#include "EngineRenderer.h"
#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "MABEngine/Renderer/Shader.h"

namespace MABEngine {

	namespace Renderer {

		SceneDataType* EngineRenderer::m_SceneData = new SceneDataType();

		void EngineRenderer::BeginScene(OrthographicCamera& camera)
		{
			m_SceneData->ViewProjectionMatrix = camera.getViewProjectionMatrix();
		}

		void EngineRenderer::EndScene()
		{
		}

		void EngineRenderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
		{
			shader->Bind();
			shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

			vertexArray->Bind();
			RenderCommand::DrawIndexed(vertexArray);
		}

	}
}