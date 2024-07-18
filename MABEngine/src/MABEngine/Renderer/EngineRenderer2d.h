#pragma once

#include <glm/glm.hpp>

#include "MABEngine/Core/Base.h"
#include "MABEngine/Camera/OrthographicCamera.h"
#include "MABEngine/Renderer/RenderAPIType.h"
#include "MABEngine/Renderer/RendererAPI.h"
#include "MABEngine/Textures/Texture2D.h"
#include "MABEngine/Textures/SubTexture2D.h"
#include "MABEngine/Renderer/EngineRenderer2dStorageStatistics.h"


namespace MABEngine {

	namespace Renderer {
		
		class MABENGINE_API EngineRenderer2d
		{
		public:
			static void Init();
			static void ShutDown();
			static void OnWindowResize(uint32_t width, uint32_t height);

			static void BeginScene(Camera::OrthographicCamera& camera);
			static void EndScene();

			static void Flush();

			inline static RendererAPIType GetCurrentAPI() { return RendererAPI::GetAPI(); }
			
			// All rotation variables are in radians
			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Core::Ref<Textures::Texture2D>& texture, const glm::vec2& tiling = { 1.0f, 1.0f });
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Core::Ref<Textures::Texture2D>& texture, const glm::vec2& tiling = { 1.0f, 1.0f });
			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Core::Ref<Textures::Texture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, const glm::vec2& tiling = { 1.0f, 1.0f });
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Core::Ref<Textures::Texture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, const glm::vec2& tiling = { 1.0f, 1.0f });

			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Core::Ref<Textures::SubTexture2D>& texture, const glm::vec2& tiling = { 1.0f, 1.0f });
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Core::Ref<Textures::SubTexture2D>& texture, const glm::vec2& tiling = { 1.0f, 1.0f });
			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Core::Ref<Textures::SubTexture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, const glm::vec2& tiling = { 1.0f, 1.0f });
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Core::Ref<Textures::SubTexture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, const glm::vec2& tiling = { 1.0f, 1.0f });


			static void ResetStats();
			static EngineRenderer2dStorageStatistics GetStats();
		private:
			static void InnerDrawQuad(
				const glm::mat4& transform,
				const glm::vec4& color,
				const glm::vec2* inputTextureCoordinate = nullptr,
				const Core::Ref<Textures::Texture2D>& texture = nullptr,
				const Core::Ref<Textures::Texture2D>& maskTexture = nullptr,
				const glm::vec2& tiling = { 1.0f, 1.0f }
			);
			static void FlushAndReset();
		};

	}
}