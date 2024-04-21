#pragma once
#include "MABEngine/Core.h"
#include "MABEngine/Renderer/ShaderDataType.h"

namespace MABEngine {

	namespace Renderer {

		struct MABENGINE_API BufferElement
		{
			ShaderDataType Type;
			std::string Name;
			bool Normalized;
			uint32_t Size;
			uint32_t Offset;

			BufferElement()
				:Type(ShaderDataType::None), Name(""), Normalized(false), Size(ShaderDataTypeSize(ShaderDataType::None)), Offset(0)
			{}

			BufferElement(ShaderDataType type, const std::string& name)
				:Type(type), Name(name), Normalized(false), Size(ShaderDataTypeSize(type)), Offset(0)
			{

			}

			BufferElement(ShaderDataType type, const std::string& name, bool normalize)
				:Type(type), Name(name), Normalized(normalize), Size(ShaderDataTypeSize(type)), Offset(0)
			{

			}

			uint32_t GetComponentCount() const;
		};

	}
}

