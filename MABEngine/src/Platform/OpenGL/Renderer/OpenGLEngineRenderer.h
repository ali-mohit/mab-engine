#pragma once

#include "MABEngine/Renderer/ShaderDataType.h"

#include <glad/glad.h>

namespace MABEngine {
	namespace Renderer {
		static GLenum ShaderDataTypToOpenGLBaseType(ShaderDataType type) {
			switch (type)
			{
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
			case ShaderDataType::Bool2:		return GL_BOOL;
			case ShaderDataType::Bool3:		return GL_BOOL;
			case ShaderDataType::Bool4:		return GL_BOOL;
			}

			return GL_INVALID_ENUM;
		}
	}
}
