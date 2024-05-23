#include "mabengine_pch.h"

#include "MABEngine/Core.h"
#include "MABEngine/Logging/Log.h"
#include "MABEngine/Renderer/ShaderPackageFile.h"

#include "MABEngine/Renderer/ShaderFileType.h"
#include "MABEngine/Renderer/RenderAPIType.h"
#include "MABEngine/Renderer/EngineRenderer.h"

namespace MABEngine {

	namespace Renderer {
		
		ShaderPackageFile::ShaderPackageFile(const std::string& name, const std::string& path, const std::string& prefix)
			:m_Name(name), m_Path(path), m_Prefix(prefix) {}

		ShaderPackageFile::~ShaderPackageFile(){}
		
		const std::string& ShaderPackageFile::GetShaderFilePath(ShaderFileType fileType) const
		{
			std::string path = m_Path;
			if (!path.empty() && path.back() != '/') {
				path += '/';
			}

			std::string postFix = GetShaderFilePostFix();
			std::string shaderTypeStr = GetShaderFileTypeName(fileType);

			return path + "/" + m_Prefix + "." + shaderTypeStr + "." + postFix;
		}

		const std::string& ShaderPackageFile::GetShaderFilePostFix() const
		{
			switch (EngineRenderer::GetCurrentAPI())
			{
			case MABEngine::Renderer::RendererAPIType::None:
				MAB_CORE_ASSERT(false, "RenderAPIType is NONE in GetShaderFilePath!");
				return ".none";

			case MABEngine::Renderer::RendererAPIType::OpenGL:
				return ".glsl";

			default:
				MAB_CORE_ASSERT(false, "system can not found Shader postfix!");
				return "";
			}
		}

		std::string ShaderPackageFile::GetShaderFileTypeName(ShaderFileType fileType) {
			switch (fileType)
			{
			case MABEngine::Renderer::ShaderFileType::None:
				return "none";
			case MABEngine::Renderer::ShaderFileType::VertexShader:
				return "vertext-shader";
			case MABEngine::Renderer::ShaderFileType::FragmentSahder:
				return "fragment-shader";
			default:
				MAB_CORE_ASSERT(false, "ShaderFileType unknown");
				return "uknown";
			}
		}
	}
}