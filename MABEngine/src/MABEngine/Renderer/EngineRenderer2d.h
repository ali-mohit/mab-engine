#pragma once

#include <glm/glm.hpp>

#include "MABEngine/Core/Base.h"
#include "MABEngine/Camera/OrthographicCamera.h"
#include "MABEngine/Renderer/RenderAPIType.h"
#include "MABEngine/Renderer/RendererAPI.h"


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

			inline static RendererAPIType GetCurrentAPI() { return RendererAPI::GetAPI(); }
			
			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		};

	}
}