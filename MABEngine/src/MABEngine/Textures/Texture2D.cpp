#include "mabengine_pch.h"
#include "MABEngine/Textures/Texture2D.h"
#include "MABEngine/Renderer/EngineRenderer.h"
#include "Platform/OpenGL/Textures/OpenGLTexture2D.h"

namespace MABEngine {
	namespace Textures {

		Ref<Texture2D> Texture2D::Create(const std::string& path)
		{
			switch (Renderer::EngineRenderer::GetCurrentAPI())
			{
			case Renderer::RendererAPIType::None:
				MAB_CORE_ASSERT(false, "RendererAPIType::None is not support. There is not any Texture2D.");
				break;
			case Renderer::RendererAPIType::OpenGL:
				return CreateRef<OpenGLTexture2D>(path);
			}

			MAB_CORE_ASSERT(false, "Texture2D that support RendererAPI is not found. it returns nullptr.");
			return nullptr;
		}

	}
}