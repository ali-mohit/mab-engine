#include "mabengine_pch.h"
#include "MABEngine/Core/Base.h"
#include "MABEngine/Logging/Log.h"
#include "MABEngine/Renderer/RenderCommand.h"
#include "MABEngine/Renderer/EngineRenderer2dStorage.h"
#include "MABEngine/Renderer/EngineRenderer2d.h"
#include "MABEngine/Renderer/ShaderPackageFile.h"
#include "MABEngine/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace MABEngine {

	namespace Renderer {

		static EngineRenderer2dStorage* s_2dRendererData;

		void EngineRenderer2d::Init()
		{
			s_2dRendererData = new EngineRenderer2dStorage();
			
			// Loading Quad	
			s_2dRendererData->QuadVertexArray = VertexArray::Create();
			float vertices[3 * 4] = {
				-0.5f, -0.5f, 0.0f,
				-0.5f,  0.5f, 0.0f,
				 0.5f,  0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
			};

			MABEngine::Core::Ref<VertexBuffer> vertexBuffer;
			vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position"},
			};
			vertexBuffer->SetLayout(layout);
			s_2dRendererData->QuadVertexArray->AddVertexBuffer(vertexBuffer);

			// Index Buffer
			unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 };
			Core::Ref<IndexBuffer> indexBuffer;
			indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
			s_2dRendererData->QuadVertexArray->AddIndexBuffer(indexBuffer);


			// Loading Shader
			ShaderPackageFile packageInfo(
				"solid",
				"assets/shaders/solid/",
				"solid."
			);
			s_2dRendererData->FlatColorShader = Shader::Create(packageInfo);
		}

		void EngineRenderer2d::ShutDown()
		{
			delete(s_2dRendererData);
		}

		void EngineRenderer2d::OnWindowResize(uint32_t width, uint32_t height)
		{
			RenderCommand::SetViewport(0, 0, width, height);
		}

		void EngineRenderer2d::BeginScene(Camera::OrthographicCamera& camera)
		{
			s_2dRendererData->FlatColorShader->Bind();
			s_2dRendererData->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
			s_2dRendererData->FlatColorShader->SetMat4("u_Transform", glm::mat4(1.0f));
		}

		void EngineRenderer2d::EndScene()
		{
		}

		void EngineRenderer2d::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
		{
			DrawQuad({ position.x, position.y, 1.0 }, size, color);
		}

		void EngineRenderer2d::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
		{
			s_2dRendererData->FlatColorShader->Bind();
			s_2dRendererData->FlatColorShader->SetFloat4("u_UniqueColor", color);

			s_2dRendererData->QuadVertexArray->Bind();
			RenderCommand::DrawIndexed(s_2dRendererData->QuadVertexArray);
		}

	}
}