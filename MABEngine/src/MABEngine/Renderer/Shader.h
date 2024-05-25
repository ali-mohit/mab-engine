#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/ShaderPackageFile.h"

#include <string>
#include <glm/glm.hpp>

namespace MABEngine {
	namespace Renderer {
		
		class MABENGINE_API Shader {
		public:
			virtual ~Shader() = default;

			virtual void Bind() const = 0;
			virtual void UnBind() const = 0;

			virtual const std::string& GetName() const = 0;

			static Core::Ref<Shader> Create(const ShaderPackageFile& packageInfo);
			static Core::Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

			virtual void SetInt(const std::string& name, int value) = 0;
			virtual void SetInt2(const std::string& name, const glm::ivec2& value) = 0;
			virtual void SetInt3(const std::string& name, const glm::ivec3& value) = 0;
			virtual void SetInt4(const std::string& name, const glm::ivec4& value) = 0;

			virtual void SetFloat(const std::string& name, float value) = 0;
			virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
			virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
			virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0; 

			virtual void SetMat3(const std::string& name, const glm::mat3& matrix) = 0;
			virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;

		};

	}
}
