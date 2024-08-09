#include "mabengine_pch.h"

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/EngineRenderer.h"

#include "MABEngine/Renderer/GraphicCardInfo.h"

#include "Platform/OpenGL/Renderer/OpenGLGraphicCardInfo.h"

namespace MABEngine {
	namespace Renderer {

		Core::Ref<GraphicCardInfo> GraphicCardInfo::Create()
		{
			switch (EngineRenderer::GetCurrentAPI())
			{
			case RendererAPIType::None:
				MAB_CORE_ASSERT(false, "RendererAPIType::None is not support. There is not any GraphicCardInfo.");
				break;
			case RendererAPIType::OpenGL:
				return Core::CreateRef<OpenGLGraphicCardInfo>();
				break;
			}

			MAB_CORE_ASSERT(false, "GraphicCardInfo that support RendererAPI is not found. it returns nullptr.");
			return nullptr;
		}

	}
}