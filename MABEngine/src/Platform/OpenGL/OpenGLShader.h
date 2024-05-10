#pragma once
#include "MABEngine/Core.h"
#include "MABEngine/Renderer/Shader.h"

#include <string>
#include <glm/glm.hpp>


namespace MABEngine {

	namespace Renderer {

		class MABENGINE_API OpenGLShader : public Shader {
		public:
			OpenGLShader(const std::string& vertextSource, const std::string fragmentSource);
			~OpenGLShader();

			virtual void Bind() const override;
			virtual void UnBind() const override;

			uint32_t GetRendererId() { return m_RendererId; }

			void UploadUniformInt(const std::string& name, int value);
			void UploadUniformInt2(const std::string& name, const glm::ivec2& value);
			void UploadUniformInt3(const std::string& name, const glm::ivec3& value);
			void UploadUniformInt4(const std::string& name, const glm::ivec4& value);


			void UploadUniformFloat(const std::string& name, float value);
			void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
			void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
			void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

			void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
			void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		private:
			uint32_t m_RendererId = 0;
		};

	}
}