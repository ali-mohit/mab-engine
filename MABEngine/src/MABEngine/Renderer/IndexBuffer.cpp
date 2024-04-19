#include "mabengine_pch.h"

#include "MABEngine/Logging/Log.h"
#include "MABEngine/Renderer/EngineRenderer.h"
#include "MABEngine/Renderer/IndexBuffer.h"

#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace MABEngine {
	namespace Renderer {

		IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
		{
			switch (EngineRenderer::GetCurrentAPI())
			{
			case RendererAPIType::None:
				MAB_CORE_ASSERT(false, "RendererAPIType::None is not support. There is not any IndexBuffer.");
				break;
			case RendererAPIType::OpenGL:
				return new OpenGLIndexBuffer(indices, count);
				break;
			}

			MAB_CORE_ASSERT(false, "IndexBuffer that support RendererAPI is not found. it returns nullptr.");
			return nullptr;
		}

	}
}