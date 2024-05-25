#include "mabengine_pch.h"

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/VertexArray.h"
#include "MABEngine/Renderer/EngineRenderer.h"
#include "MABEngine/Renderer/RenderAPIType.h"

#include "Platform/OpenGL/Renderer/OpenGLVertexArray.h"

namespace MABEngine {

	namespace Renderer {
		Core::Ref<VertexArray> VertexArray::Create()
		{

			switch (EngineRenderer::GetCurrentAPI())
			{
			case RendererAPIType::None:
				MAB_CORE_ASSERT(false, "RendererAPIType::None is not support. There is not any VertexArray.");
				break;
			case RendererAPIType::OpenGL:
				return Core::CreateRef<OpenGLVertexArray>();
				break;
			}

			MAB_CORE_ASSERT(false, "VertexArray that support RendererAPI is not found. it returns nullptr.");
			return nullptr;
		}
	}
}