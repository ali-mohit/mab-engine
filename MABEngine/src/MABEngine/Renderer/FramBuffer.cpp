#include "mabengine_pch.h"
#include "MABEngine/Renderer/FramBuffer.h"
#include "MABEngine/Renderer/EngineRenderer.h"

#include "Platform/OpenGL/Renderer/OpenGLFrameBuffer.h"

namespace MABEngine {

	namespace Renderer {
		Core::Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
		{
			switch (EngineRenderer::GetCurrentAPI())
			{
			case RendererAPIType::None:
				MAB_CORE_ASSERT(false, "RendererAPIType::None is not support. There is not any FrameBuffer.");
				break;
			case RendererAPIType::OpenGL:
				return Core::CreateRef<OpenGLFrameBuffer>(spec);
				break;
			}

			MAB_CORE_ASSERT(false, "FrameBuffer that support RendererAPI is not found. it returns nullptr.");
			return nullptr;
		}
	}
}