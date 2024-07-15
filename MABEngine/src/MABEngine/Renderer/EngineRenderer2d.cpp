#include "mabengine_pch.h"
#include "MABEngine/Core/Base.h"
#include "MABEngine/Logging/Log.h"
#include "MABEngine/Renderer/RenderCommand.h"
#include "MABEngine/Renderer/EngineRenderer2dStorage.h"
#include "MABEngine/Renderer/EngineRenderer2d.h"
#include "MABEngine/Renderer/ShaderPackageFile.h"
#include "MABEngine/Renderer/Shader.h"
#include "MABEngine/Renderer/QuadVertexInfo.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace MABEngine {

	namespace Renderer {

		static EngineRenderer2dStorage* s_2dRendererData;

		void EngineRenderer2d::Init()
		{
			MAB_PROFILE_FUNCTION();

			s_2dRendererData = new EngineRenderer2dStorage();
			
			// Loading Quad
			s_2dRendererData->QuadVertexArray = VertexArray::Create();
			s_2dRendererData->QuadVertexBuffer.reset(VertexBuffer::Create(s_2dRendererData->MAX_VERTICES * sizeof(QuadVertexInfo)));
			BufferLayout layout = {
				{ ShaderDataType::Float4,	"a_Position" },
				{ ShaderDataType::Float4,	"a_Color" },
				{ ShaderDataType::Float2,	"a_TexCoord" },
				{ ShaderDataType::Float2,   "a_Tiling"},
				{ ShaderDataType::Float,	"a_TextureId" },
				{ ShaderDataType::Float,	"a_TextureMaskId" },
				{ ShaderDataType::Float,	"a_TransformIndex" },
			};
			s_2dRendererData->QuadVertexBuffer->SetLayout(layout);
			s_2dRendererData->QuadVertexArray->AddVertexBuffer(s_2dRendererData->QuadVertexBuffer);

			// Index Buffer
			s_2dRendererData->QuadIndexBuffer.reset(IndexBuffer::Create(s_2dRendererData->MAX_INDICES * sizeof(uint32_t), sizeof(uint32_t)));
			s_2dRendererData->QuadVertexArray->SetIndexBuffer(s_2dRendererData->QuadIndexBuffer);
			
			//Generate VertexInfoArray and Edge
			s_2dRendererData->QuadVertexInfoBase = new QuadVertexInfo[s_2dRendererData->MAX_VERTICES];
			s_2dRendererData->QuadIndexEdgeBase = new uint32_t[s_2dRendererData->MAX_INDICES];

			// Loading Texture Shader
			ShaderPackageFile packageTextureInfo(
				"basic-2dbatchrender-texture",
				"assets/shaders/basic-2dbatchrender-texture/",
				"basic-2dbatchrender-texture."
			);

			int* sampler = new int[s_2dRendererData->MAX_TEXTURE_UNIT];
			for (uint32_t i = 0; i < s_2dRendererData->MAX_TEXTURE_UNIT; i++)
			{
				sampler[i] = i;
			}

			s_2dRendererData->ShaderObject = Shader::Create(packageTextureInfo);
			s_2dRendererData->ShaderObject->Bind();
			s_2dRendererData->ShaderObject->SetIntArray("u_Textures", sampler, s_2dRendererData->MAX_TEXTURE_UNIT);
			s_2dRendererData->ShaderObject->UnBind();
			
			delete[] sampler;
			sampler = nullptr;

			//Define White Texture
			s_2dRendererData->WhiteTexture = Textures::Texture2D::Create(1, 1);
			uint32_t whiteTextureData = 0xffffffff;
			s_2dRendererData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
			s_2dRendererData->AddTextureInToLib(s_2dRendererData->WhiteTexture);


			s_2dRendererData->VertexPositionTemplate[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
			s_2dRendererData->VertexPositionTemplate[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
			s_2dRendererData->VertexPositionTemplate[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
			s_2dRendererData->VertexPositionTemplate[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
		}

		void EngineRenderer2d::ShutDown() {
			MAB_PROFILE_FUNCTION();

			delete[] s_2dRendererData->QuadIndexEdgeBase;
			delete[] s_2dRendererData->QuadVertexInfoBase;

			s_2dRendererData->QuadVertexInfoBase = nullptr;
			s_2dRendererData->QuadVertexInfoPtr = nullptr;
			s_2dRendererData->QuadIndexEdgeBase = nullptr;

			delete(s_2dRendererData);
		}

		void EngineRenderer2d::OnWindowResize(uint32_t width, uint32_t height)
		{
			RenderCommand::SetViewport(0, 0, width, height);
		}

		void EngineRenderer2d::BeginScene(Camera::OrthographicCamera& camera)
		{
			MAB_PROFILE_FUNCTION();

			s_2dRendererData->ShaderObject->Bind();
			s_2dRendererData->ShaderObject->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

			s_2dRendererData->QuadVertexInfoPtr = s_2dRendererData->QuadVertexInfoBase;

			s_2dRendererData->QuadIndexCount += 0;
			s_2dRendererData->QuadEdgeCount += 0;
		}

		void EngineRenderer2d::EndScene()
		{
			MAB_PROFILE_FUNCTION();

			uint32_t vertexInfoSize = (uint8_t*)s_2dRendererData->QuadVertexInfoPtr - (uint8_t*)s_2dRendererData->QuadVertexInfoBase;
			s_2dRendererData->QuadVertexBuffer->SetData(s_2dRendererData->QuadVertexInfoBase, vertexInfoSize);

			uint32_t edgeSize = s_2dRendererData->QuadEdgeCount * sizeof(uint32_t);
			s_2dRendererData->QuadIndexBuffer->SetData(s_2dRendererData->QuadIndexEdgeBase, edgeSize);

			Flush();
		}

		void EngineRenderer2d::Flush()
		{
			MAB_PROFILE_FUNCTION();

			for (const auto& pair : s_2dRendererData->TextureLib) {
				uint32_t slotId = s_2dRendererData->TextureLibIndex[pair.first];
				
				pair.second->Bind(slotId);
			}

			RenderCommand::DrawIndexed(s_2dRendererData->QuadVertexArray, s_2dRendererData->QuadIndexCount);
		}

		void EngineRenderer2d::DrawQuad(
			const glm::vec2& position,
			const glm::vec2& size,
			const glm::vec4& color
		) {
			DrawQuad({ position.x, position.y, 1.0 }, size, color);
		}

		void EngineRenderer2d::DrawQuad(
			const glm::vec3& position,
			const glm::vec2& size,
			const glm::vec4& color
		) {
			MAB_PROFILE_FUNCTION();
			
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
				* glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

			InnerDrawQuad(transform, color);
		}

		void EngineRenderer2d::DrawQuad(
			const glm::vec2& position,
			const glm::vec2& size,
			float rotation,
			const glm::vec4& color
		) {
			DrawQuad({ position.x, position.y, 1.0 }, size, rotation, color);
		}

		void EngineRenderer2d::DrawQuad(
			const glm::vec3& position,
			const glm::vec2& size,
			float rotation,
			const glm::vec4& color
		) {
			MAB_PROFILE_FUNCTION();

			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
				* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

			InnerDrawQuad(transform, color);
		}

		void EngineRenderer2d::DrawQuad(
			const glm::vec2& position,
			const glm::vec2& size,
			const Core::Ref<Textures::Texture2D>& texture,
			const glm::vec2& tiling
		) {
			DrawQuad({ position.x, position.y, 1.0 }, size, texture, tiling);
		}

		void EngineRenderer2d::DrawQuad(
			const glm::vec3& position,
			const glm::vec2& size,
			const Core::Ref<Textures::Texture2D>& texture,
			const glm::vec2& tiling
		) {
			MAB_PROFILE_FUNCTION();

			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
				* glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

			float textureId = s_2dRendererData->AddTextureInToLib(texture);
			InnerDrawQuad(transform, {1.0f, 1.0f, 1.0f, 1.0f}, textureId, 0, tiling);
		}

		void EngineRenderer2d::DrawQuad(
			const glm::vec2& position,
			const glm::vec2& size,
			float rotation,
			const Core::Ref<Textures::Texture2D>& texture,
			const glm::vec4& color,
			const glm::vec2& tiling
		) {
			DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture, color, tiling);
		}

		void EngineRenderer2d::DrawQuad(
			const glm::vec3& position,
			const glm::vec2& size,
			float rotation,
			const Core::Ref<Textures::Texture2D>& texture,
			const glm::vec4& color,
			const glm::vec2& tiling
		) {
			MAB_PROFILE_FUNCTION();

			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
				* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
			
			
			float textureId = s_2dRendererData->AddTextureInToLib(texture);
			InnerDrawQuad(transform, color, textureId, 0, tiling);
		}

		void EngineRenderer2d::InnerDrawQuad(
			const glm::mat4& transform,
			const glm::vec4& color,
			float textureId,
			float maskTextureId,
			const glm::vec2& tiling
		)
		{
			s_2dRendererData->QuadVertexInfoPtr->Position = transform * s_2dRendererData->VertexPositionTemplate[0];
			s_2dRendererData->QuadVertexInfoPtr->Color = color;
			s_2dRendererData->QuadVertexInfoPtr->TextCoordinate = { 0.0f, 0.0f };
			s_2dRendererData->QuadVertexInfoPtr->Tiling = tiling;
			s_2dRendererData->QuadVertexInfoPtr->TextureId = textureId;
			s_2dRendererData->QuadVertexInfoPtr->TextureMaskId = maskTextureId;
			s_2dRendererData->QuadVertexInfoPtr++;

			s_2dRendererData->QuadVertexInfoPtr->Position = transform * s_2dRendererData->VertexPositionTemplate[1];
			s_2dRendererData->QuadVertexInfoPtr->Color = color;
			s_2dRendererData->QuadVertexInfoPtr->TextCoordinate = { 1.0f, 0.0f };
			s_2dRendererData->QuadVertexInfoPtr->Tiling = tiling;
			s_2dRendererData->QuadVertexInfoPtr->TextureId = textureId;
			s_2dRendererData->QuadVertexInfoPtr->TextureMaskId = maskTextureId;
			s_2dRendererData->QuadVertexInfoPtr++;

			s_2dRendererData->QuadVertexInfoPtr->Position = transform * s_2dRendererData->VertexPositionTemplate[2];
			s_2dRendererData->QuadVertexInfoPtr->Color = color;
			s_2dRendererData->QuadVertexInfoPtr->TextCoordinate = { 1.0f, 1.0f };
			s_2dRendererData->QuadVertexInfoPtr->Tiling = tiling;
			s_2dRendererData->QuadVertexInfoPtr->TextureId = textureId;
			s_2dRendererData->QuadVertexInfoPtr->TextureMaskId = maskTextureId;
			s_2dRendererData->QuadVertexInfoPtr++;

			s_2dRendererData->QuadVertexInfoPtr->Position = transform * s_2dRendererData->VertexPositionTemplate[3];
			s_2dRendererData->QuadVertexInfoPtr->Color = color;
			s_2dRendererData->QuadVertexInfoPtr->TextCoordinate = { 0.0f, 1.0f };
			s_2dRendererData->QuadVertexInfoPtr->Tiling = tiling;
			s_2dRendererData->QuadVertexInfoPtr->TextureId = textureId;
			s_2dRendererData->QuadVertexInfoPtr->TextureMaskId = maskTextureId;
			s_2dRendererData->QuadVertexInfoPtr++;

			uint32_t offset = s_2dRendererData->QuadEdgeCount;
			uint32_t vertexCode = s_2dRendererData->QuadIndexCount;
			s_2dRendererData->QuadIndexEdgeBase[offset + 0] = vertexCode + 0;
			s_2dRendererData->QuadIndexEdgeBase[offset + 1] = vertexCode + 1;
			s_2dRendererData->QuadIndexEdgeBase[offset + 2] = vertexCode + 2;

			s_2dRendererData->QuadIndexEdgeBase[offset + 3] = vertexCode + 2;
			s_2dRendererData->QuadIndexEdgeBase[offset + 4] = vertexCode + 3;
			s_2dRendererData->QuadIndexEdgeBase[offset + 5] = vertexCode + 0;

			s_2dRendererData->QuadIndexCount += 4;
			s_2dRendererData->QuadEdgeCount += 6;
		}

	}
}