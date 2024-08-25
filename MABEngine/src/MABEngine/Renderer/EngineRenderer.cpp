#include "mabengine_pch.h"
#include "EngineRenderer.h"
#include "RenderCommand.h"

#include "MABEngine/Renderer/Shader.h"
#include "MABEngine/Camera/OrthographicCamera.h"
#include "MABEngine/Camera/PerspectiveCamera.h"
#include "MABEngine/Renderer/EngineRenderer2d.h"

namespace MABEngine {

	namespace Renderer {

		SceneDataType* EngineRenderer::m_SceneData = new SceneDataType();

		void EngineRenderer::Init()
		{
			MAB_PROFILE_FUNCTION();

			RenderCommand::Init();
			EngineRenderer2d::Init();
		}

		void EngineRenderer::Shutdown()
		{
			EngineRenderer2d::ShutDown();
		}

		void EngineRenderer::OnWindowResize(uint32_t width, uint32_t height)
		{
			RenderCommand::SetViewport(0, 0, width, height);
		}

		void EngineRenderer::BeginScene(Camera::OrthographicCamera& camera)
		{
			m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

			if (m_SceneData->PipelineConfig.IsChanged) {
				RenderCommand::SetPipelineConfig(m_SceneData->PipelineConfig);
				m_SceneData->PipelineConfig.IsChanged = false;
			}
		}
		void EngineRenderer::BeginScene(Camera::PerspectiveCamera& camera)
		{
			m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

			if (m_SceneData->PipelineConfig.IsChanged) {
				RenderCommand::SetPipelineConfig(m_SceneData->PipelineConfig);
				m_SceneData->PipelineConfig.IsChanged = false;
			}
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

			RenderCommand::DrawIndexed(vertexArray);
		}

		void EngineRenderer::SubmitLines(
			const Core::Ref<Shader>& shader, const Core::Ref<VertexArray>& vertexArray, const glm::mat4& transform)
		{
			shader->Bind();
			shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
			shader->SetMat4("u_Transform", transform);

			RenderCommand::DrawLines(vertexArray);
		}

		void EngineRenderer::SetRenderMode(const RenderModeType& renderMode)
		{
			m_SceneData->PipelineConfig.RenderMode = renderMode;
			m_SceneData->PipelineConfig.IsChanged = true;
		}
		const RenderModeType& EngineRenderer::GetRenderMode()
		{
			return m_SceneData->PipelineConfig.RenderMode;
		}

		void EngineRenderer::SetRenderFaceMode(const RenderFaceMode& faceMode)
		{
			m_SceneData->PipelineConfig.FaceMode = faceMode;
			m_SceneData->PipelineConfig.IsChanged = true;
		}
		const RenderFaceMode& EngineRenderer::GetRenderFaceMode()
		{
			return m_SceneData->PipelineConfig.FaceMode;
		}



	}
}