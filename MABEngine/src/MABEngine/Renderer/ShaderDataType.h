#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Logging/Log.h"

#include <cstdint>

namespace MABEngine {

	namespace Renderer {
		enum class MABENGINE_API ShaderDataType
		{
			None = 0,
			Float = 10,
			Float2 = 20,
			Float3 = 30,
			Float4 = 40,

			Mat3 = 50,
			Mat4 = 60,

			Int = 70,
			Int2 = 80,
			Int3 = 90,
			Int4 = 100,

			Bool = 110,
			Bool2 = 120,
			Bool3 = 130,
			Bool4 = 140,
		};

		static uint32_t ShaderDataTypeSize(ShaderDataType type) {
			switch (type)
			{
			case MABEngine::Renderer::ShaderDataType::Float:    return sizeof(float) * 1;
			case MABEngine::Renderer::ShaderDataType::Float2:	return sizeof(float) * 2;
			case MABEngine::Renderer::ShaderDataType::Float3:	return sizeof(float) * 3;
			case MABEngine::Renderer::ShaderDataType::Float4:	return sizeof(float) * 4;

			case MABEngine::Renderer::ShaderDataType::Mat3:		return sizeof(float) * 3 * 3;
			case MABEngine::Renderer::ShaderDataType::Mat4:		return sizeof(float) * 4 * 4;

			case MABEngine::Renderer::ShaderDataType::Int:		return sizeof(int);
			case MABEngine::Renderer::ShaderDataType::Int2:		return sizeof(int) * 2;
			case MABEngine::Renderer::ShaderDataType::Int3:		return sizeof(int) * 3;
			case MABEngine::Renderer::ShaderDataType::Int4:		return sizeof(int) * 4;

			case MABEngine::Renderer::ShaderDataType::Bool:		return sizeof(bool);
			case MABEngine::Renderer::ShaderDataType::Bool2:	return sizeof(bool) * 2;
			case MABEngine::Renderer::ShaderDataType::Bool3:	return sizeof(bool) * 3;
			case MABEngine::Renderer::ShaderDataType::Bool4:	return sizeof(bool) * 4;
			
			default:
				MAB_CORE_ERROR("{0}", (int)type);
				MAB_CORE_ASSERT(false, "ShaderDataType Not found!");
			}

			return 0;
		}
	}
}