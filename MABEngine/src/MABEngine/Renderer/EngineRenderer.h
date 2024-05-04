#pragma once

#include "MABEngine/Core.h"
#include "MABEngine/Renderer/RendererAPI.h"
#include "MABEngine/Renderer/RenderAPIType.h"
#include "MABEngine/Renderer/VertexArray.h"
#include "MABEngine/Renderer/OrthographicCamera.h"
#include "MABEngine/Renderer/SceneDataType.h"
#include "MABEngine/Renderer/Shader.h"

namespace MABEngine {

	namespace Renderer {

		class MABENGINE_API EngineRenderer
		{
		public:
			static void BeginScene(OrthographicCamera& camera);
			static void EndScene();

			static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

			inline static RendererAPIType GetCurrentAPI() { return RendererAPI::GetAPI(); }
		private:
			static SceneDataType* m_SceneData;
		};

	}
}


