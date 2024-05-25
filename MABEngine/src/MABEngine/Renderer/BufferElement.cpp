#include "mabengine_pch.h"
#include "BufferElement.h"
#include "MABEngine/Core/Base.h"
#include "MABEngine/Logging/Log.h"

namespace MABEngine {
    namespace Renderer {

        uint32_t BufferElement::GetComponentCount() const
        {
            switch (Type)
            {
			case MABEngine::Renderer::ShaderDataType::Float:    return 1;
			case MABEngine::Renderer::ShaderDataType::Float2:	return 2;
			case MABEngine::Renderer::ShaderDataType::Float3:	return 3;
			case MABEngine::Renderer::ShaderDataType::Float4:	return 4;

			case MABEngine::Renderer::ShaderDataType::Mat3:		return 3 * 3;
			case MABEngine::Renderer::ShaderDataType::Mat4:		return 4 * 4;

			case MABEngine::Renderer::ShaderDataType::Int:		return 1;
			case MABEngine::Renderer::ShaderDataType::Int2:		return 2;
			case MABEngine::Renderer::ShaderDataType::Int3:		return 3;
			case MABEngine::Renderer::ShaderDataType::Int4:		return 4;

			case MABEngine::Renderer::ShaderDataType::Bool:		return 1;
			case MABEngine::Renderer::ShaderDataType::Bool2:	return 2;
			case MABEngine::Renderer::ShaderDataType::Bool3:	return 3;
			case MABEngine::Renderer::ShaderDataType::Bool4:	return 4;

			default:
				MAB_CORE_ERROR("{0}", (int)Type);
				MAB_CORE_ASSERT(false, "ShaderDataType Not found! (GetComponentCount)");
			}

			return 0;
        }
    }
}

