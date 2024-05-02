#include "mabengine_pch.h"
#include "VertexArray.h"
#include "MABEngine/Renderer/EngineRenderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "MABEngine/Renderer/RenderAPIType.h"

namespace MABEngine {

	namespace Renderer {
		VertexArray* VertexArray::Create()
		{

			switch (EngineRenderer::GetCurrentAPI())
			{
			case RendererAPIType::None:
				MAB_CORE_ASSERT(false, "RendererAPIType::None is not support. There is not any VertexArray.");
				break;
			case RendererAPIType::OpenGL:
				return new OpenGLVertexArray();
				break;
			}

			MAB_CORE_ASSERT(false, "VertexArray that support RendererAPI is not found. it returns nullptr.");
			return nullptr;
		}
	}
}