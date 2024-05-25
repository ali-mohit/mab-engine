#pragma once
#include "MABEngine/Core/Base.h"
#include "MABEngine/Logging/Log.h"

namespace MABEngine {

	namespace Renderer {
		enum class MABENGINE_API ShaderFileType
		{
			None = 0,
			VertexShader = 10,
			FragmentSahder = 20,
		};

		inline static std::string ShaderFileTypeToString(ShaderFileType file) {
			switch (file)
			{
			case MABEngine::Renderer::ShaderFileType::None:
				return "None";
			case MABEngine::Renderer::ShaderFileType::VertexShader:
				return "VertexShader";
			case MABEngine::Renderer::ShaderFileType::FragmentSahder:
				return "FragmentSahder";
			}

			return "ShaderFileType(???)=" + std::to_string((int)file);
		}
	}
}