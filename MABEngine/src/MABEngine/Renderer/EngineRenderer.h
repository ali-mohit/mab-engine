#pragma once

#include "MABEngine/Core.h"
#include "MABEngine/Renderer/RendererAPI.h"
#include "MABEngine/Renderer/RenderAPIType.h"
#include "MABEngine/Renderer/VertexArray.h"


namespace MABEngine {

	namespace Renderer {

		class MABENGINE_API EngineRenderer
		{
		public:
			static void BeginScene();
			static void EndScene();

			static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

			inline static RendererAPIType GetCurrentAPI() { return RendererAPI::GetAPI(); }
		};

	}
}


