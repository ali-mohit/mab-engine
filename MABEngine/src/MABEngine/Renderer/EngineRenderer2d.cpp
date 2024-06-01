#include "mabengine_pch.h"
#include "MABEngine/Core/Base.h"
#include "MABEngine/Logging/Log.h"
#include "MABEngine/Renderer/RenderCommand.h"
#include "MABEngine/Renderer/EngineRenderer2dStorage.h"
#include "MABEngine/Renderer/EngineRenderer2d.h"
#include "MABEngine/Renderer/ShaderPackageFile.h"
#include "MABEngine/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace MABEngine {

	namespace Renderer {

		static EngineRenderer2dStorage* s_2dRendererData;

		void EngineRenderer2d::Init()
		{
			s_2dRendererData = new EngineRenderer2dStorage();
			
			// Loading Quad	
			s_2dRendererData->QuadVertexArray = VertexArray::Create();
			float vertices[5 * 4] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			};

			MABEngine::Core::Ref<VertexBuffer> vertexBuffer;
			vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position"},
				{ ShaderDataType::Float2, "a_TexCoord"},

			};
			vertexBuffer->SetLayout(layout);
			s_2dRendererData->QuadVertexArray->AddVertexBuffer(vertexBuffer);

			// Index Buffer
			unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 };
			Core::Ref<IndexBuffer> indexBuffer;
			indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
			s_2dRendererData->QuadVertexArray->AddIndexBuffer(indexBuffer);

			//Define White Texture
			s_2dRendererData->WhiteTexture = Textures::Texture2D::Create(1, 1);
			uint32_t whiteTextureData = 0xffffffff;
			s_2dRendererData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

			// Loading Texture Shader
			ShaderPackageFile packageTextureInfo(
				"solid",
				"assets/shaders/basic-texture/",
				"basic-texture."
			);
			s_2dRendererData->TextureShader = Shader::Create(packageTextureInfo);

			s_2dRendererData->TextureShader->Bind();
			s_2dRendererData->TextureShader->SetInt("u_Texture", 0);
			s_2dRendererData->TextureShader->UnBind();
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
			s_2dRendererData->TextureShader->Bind();
			s_2dRendererData->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
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
			s_2dRendererData->TextureShader->Bind();
			s_2dRendererData->TextureShader->SetFloat4("u_UniqueColor", color);
			s_2dRendererData->WhiteTexture->Bind();

			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
				glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
			s_2dRendererData->TextureShader->SetMat4("u_Transform", transform);

			s_2dRendererData->QuadVertexArray->Bind();
			RenderCommand::DrawIndexed(s_2dRendererData->QuadVertexArray);
			s_2dRendererData->WhiteTexture->UnBind();
		}

		void EngineRenderer2d::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Core::Ref<Textures::Texture2D>& texture)
		{
			DrawQuad({ position.x, position.y, 1.0 }, size, texture);
		}

		void EngineRenderer2d::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Core::Ref<Textures::Texture2D>& texture)
		{
			s_2dRendererData->TextureShader->Bind();
			s_2dRendererData->TextureShader->SetFloat4("u_UniqueColor", glm::vec4(1.0f));
			texture->Bind();

			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
				glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
			s_2dRendererData->TextureShader->SetMat4("u_Transform", transform);

			s_2dRendererData->TextureShader->Bind();
			RenderCommand::DrawIndexed(s_2dRendererData->QuadVertexArray);
			texture->UnBind();
		}

	}
}