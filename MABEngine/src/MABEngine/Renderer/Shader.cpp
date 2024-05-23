#include "mabengine_pch.h"
#include "MABEngine/Logging/Log.h"
#include "MABEngine/Renderer/Shader.h"
#include "MABEngine/Renderer/ShaderPackageFile.h"
#include "MABEngine/Renderer/EngineRenderer.h"
#include "MABEngine/Renderer/RenderAPIType.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace MABEngine {

	namespace Renderer {
		Ref<Shader> Shader::Create(const ShaderPackageFile& packageInfo) {
			switch (EngineRenderer::GetCurrentAPI())
			{
			case RendererAPIType::None:
				MAB_CORE_ASSERT(false, "RendererAPIType::None is not support. There is not any Shader.");
				break;
			case RendererAPIType::OpenGL:
				return CreateRef<OpenGLShader>(packageInfo);
				break;
			}

			MAB_CORE_ASSERT(false, "Shader that support RendererAPI is not found. it returns nullptr.");
			return nullptr;
		}

		Ref<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource) {
			switch (EngineRenderer::GetCurrentAPI())
			{
			case RendererAPIType::None:
				MAB_CORE_ASSERT(false, "RendererAPIType::None is not support. There is not any Shader.");
				break;
			case RendererAPIType::OpenGL:
				return CreateRef<OpenGLShader>(vertexSource, fragmentSource);
				break;
			}

			MAB_CORE_ASSERT(false, "Shader that support RendererAPI is not found. it returns nullptr.");
			return nullptr;
		}
	}

}