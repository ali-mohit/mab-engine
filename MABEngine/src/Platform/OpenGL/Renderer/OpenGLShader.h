#pragma once
#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/Shader.h"
#include "MABEngine/Renderer/ShaderPackageFile.h"
#include "MABEngine/Renderer/ShaderFileType.h"

#include <string>
#include <glm/glm.hpp>


namespace MABEngine {

	namespace Renderer {

		class MABENGINE_API OpenGLShader : public Shader {
		public:
			OpenGLShader(const std::string& name, const std::string& vertextSource, const std::string& fragmentSource);
			OpenGLShader(const ShaderPackageFile& packageInfo);
			~OpenGLShader();

			virtual void Bind() const override;
			virtual void UnBind() const override;

			uint32_t GetRendererId() { return m_RendererId; }

			virtual const std::string& GetName() const override { return m_Name; }

			virtual void SetInt(const std::string& name, int value) override;
			virtual void SetInt2(const std::string& name, const glm::ivec2& value) override;
			virtual void SetInt3(const std::string& name, const glm::ivec3& value) override;
			virtual void SetInt4(const std::string& name, const glm::ivec4& value) override;

			virtual void SetFloat(const std::string& name, float value) override;
			virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
			virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
			virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;

			virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
			virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;

			virtual void SetMat3Array(const std::string& name, const  std::vector<glm::mat3>& matrixList) override;
			virtual void SetMat4Array(const std::string& name, const  std::vector<glm::mat4>& matrixList) override;

			virtual void SetIntArray(const std::string& name, int* values, int count) override;
			virtual void SetFloatArray(const std::string& name, float* values, int count) override;
		
		private:
			std::string ReadFileContent(const std::string& filePath);
			unsigned int ConvertShaderFileTypeToGLenum(ShaderFileType fileType);
			void Compile(const std::unordered_map<ShaderFileType, std::string>& shadersContent);

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
			
			void UploadUniformMat3Array(const std::string& name, const std::vector<glm::mat3>& matrixList);
			void UploadUniformMat4Array(const std::string& name, const std::vector<glm::mat4>& matrixList);

			void UploadUniformIntArray(const std::string& name, int* values, int count);
			void UploadUniformFloatArray(const std::string& name, float* values, int count);
		private:
			uint32_t m_RendererId = 0;
			std::string m_Name = "";
		};

	}
}