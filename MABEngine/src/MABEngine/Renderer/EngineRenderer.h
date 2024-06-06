#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/RendererAPI.h"
#include "MABEngine/Renderer/RenderAPIType.h"
#include "MABEngine/Renderer/VertexArray.h"
#include "MABEngine/Renderer/SceneDataType.h"
#include "MABEngine/Renderer/Shader.h"

#include "MABEngine/Camera/OrthographicCamera.h"

namespace MABEngine {

	namespace Renderer {

		class MABENGINE_API EngineRenderer
		{
		public:
			static void Init();
			static void Shutdown();

			static void OnWindowResize(uint32_t width, uint32_t height);

			static void BeginScene(Camera::OrthographicCamera& camera);
			static void EndScene();

			static void Submit(
				const Core::Ref<Shader>& shader,
				const Core::Ref<VertexArray>& vertexArray, 
				const glm::mat4& transform= glm::mat4(1.0f)
			);

			inline static RendererAPIType GetCurrentAPI() { return RendererAPI::GetAPI(); }
		private:
			static SceneDataType* m_SceneData;
		};

	}
}


