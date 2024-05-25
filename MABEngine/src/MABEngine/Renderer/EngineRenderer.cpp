#include "mabengine_pch.h"
#include "EngineRenderer.h"
#include "RenderCommand.h"

#include "MABEngine/Renderer/Shader.h"
#include "MABEngine/Camera/OrthographicCamera.h"


namespace MABEngine {

	namespace Renderer {

		SceneDataType* EngineRenderer::m_SceneData = new SceneDataType();

		void EngineRenderer::Init()
		{
			RenderCommand::Init();
		}

		void EngineRenderer::OnWindowResize(uint32_t width, uint32_t height)
		{
			RenderCommand::SetViewport(0, 0, width, height);
		}

		void EngineRenderer::BeginScene(Camera::OrthographicCamera& camera)
		{
			m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		}

		void EngineRenderer::EndScene()
		{
		}

		void EngineRenderer::Submit(
			const Core::Ref<Shader>& shader, const Core::Ref<VertexArray>& vertexArray, const glm::mat4& transform)
		{
			shader->Bind();
			shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
			shader->SetMat4("u_Transform", transform);

			vertexArray->Bind();
			RenderCommand::DrawIndexed(vertexArray);
		}

	}
}