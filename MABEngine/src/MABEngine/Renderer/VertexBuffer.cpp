#include "mabengine_pch.h"

#include "MABEngine/Logging/Log.h"
#include "MABEngine/Renderer/EngineRenderer.h"
#include "MABEngine/Renderer/RenderAPIType.h"
#include "MABEngine/Renderer/VertexBuffer.h"

#include "Platform/OpenGL/Renderer/OpenGLVertexBuffer.h"

namespace MABEngine {
	namespace Renderer {

		VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
		{
			switch (EngineRenderer::GetCurrentAPI())
			{
			case RendererAPIType::None:
				MAB_CORE_ASSERT(false, "RendererAPIType::None is not support. There is not any VertexBuffer.");
				break;
			case RendererAPIType::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
				break;
			}

			MAB_CORE_ASSERT(false, "VertexBuffer that support RendererAPI is not found. it returns nullptr.");
			return nullptr;
		}

		VertexBuffer* VertexBuffer::Create(uint32_t size)
		{
			switch (EngineRenderer::GetCurrentAPI())
			{
			case RendererAPIType::None:
				MAB_CORE_ASSERT(false, "RendererAPIType::None is not support. There is not any VertexBuffer.");
				break;
			case RendererAPIType::OpenGL:
				return new OpenGLVertexBuffer(size);
				break;
			}

			MAB_CORE_ASSERT(false, "VertexBuffer that support RendererAPI is not found. it returns nullptr.");
			return nullptr;
		}
	}
}