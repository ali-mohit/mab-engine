#include "mabengine_pch.h"
#include "MABEngine/Core.h"
#include "MABEngine/Logging/Log.h"
#include "MABEngine/Renderer/ShaderFileType.h"
#include "MABEngine/Renderer/ShaderPackageFile.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>
#include <filesystem>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>



namespace MABEngine {

	namespace Renderer {

		OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
			:m_RendererId(0), m_Name(name)
		{
			std::unordered_map<ShaderFileType, std::string> shaderContents;
			shaderContents[ShaderFileType::VertexShader] = vertexSource;
			shaderContents[ShaderFileType::FragmentSahder] = fragmentSource;

			Compile(shaderContents);
		}
		
		OpenGLShader::OpenGLShader(const ShaderPackageFile& packageInfo)
			:m_RendererId(0), m_Name(packageInfo.GetName())
		{
			std::string vertexShaderPath = packageInfo.GetShaderFilePath(ShaderFileType::VertexShader);
			std::string fragmentShaderPath = packageInfo.GetShaderFilePath(ShaderFileType::FragmentSahder);

			if (!std::filesystem::exists(vertexShaderPath)) {
				MAB_CORE_ERROR("Vertext shader path: {0} not found!", vertexShaderPath);
				MAB_CORE_ASSERT(false, "Vertext shader is not in the package!");
			}

			if (!std::filesystem::exists(fragmentShaderPath)) {
				MAB_CORE_ERROR("Fragment shader path: {0} not found!", fragmentShaderPath);
				MAB_CORE_ASSERT(false, "Fragment shader is not in the package!");
			}

			std::unordered_map<ShaderFileType, std::string> shaderContents;
			shaderContents[ShaderFileType::VertexShader] = ReadFileContent(vertexShaderPath);
			shaderContents[ShaderFileType::FragmentSahder] = ReadFileContent(fragmentShaderPath);

			Compile(shaderContents);
		}

		OpenGLShader::~OpenGLShader()
		{
			glDeleteProgram(m_RendererId);
		}

		void OpenGLShader::Bind() const
		{
			glUseProgram(m_RendererId);
		}

		void OpenGLShader::UnBind() const
		{
			glUseProgram(0);
		}

		std::string OpenGLShader::ReadFileContent(const std::string& filePath)
		{
			std::string result = "";

			if (!std::filesystem::exists(filePath)) {
				MAB_CORE_ERROR("file {0} not found!", filePath);
				return result;
			}

			std::ifstream inputFile(filePath, std::ios::in | std::ios::binary);
			if (!inputFile) {
				MAB_CORE_ERROR("System can not read file: {0}", filePath);
			}

			inputFile.seekg(0, std::ios::end);
			result.resize(inputFile.tellg());

			inputFile.seekg(0, std::ios::beg);
			inputFile.read(&result[0], result.size());

			inputFile.close();

			return result;
		}

		GLenum OpenGLShader::ConvertShaderFileTypeToGLenum(ShaderFileType fileType)
		{
			switch (fileType)
			{
			case MABEngine::Renderer::ShaderFileType::VertexShader:
				return GL_VERTEX_SHADER;
			case MABEngine::Renderer::ShaderFileType::FragmentSahder:
				return GL_FRAGMENT_SHADER;
			}

			MAB_CORE_ERROR("there is no one-to-one relation between ShaderFileType {0} and GLenum", ShaderFileTypeToString(fileType));
			MAB_CORE_ASSERT(false, "can not convert ShaderFileType to GLenum!");

			return 0;
		}

		void OpenGLShader::Compile(const std::unordered_map<ShaderFileType, std::string>& shadersContent)
		{
			// Get a program object.
			GLuint program = glCreateProgram();

			std::vector<GLuint> glShaderIDs;
			glShaderIDs.reserve(shadersContent.size());

			for (auto& kv : shadersContent) {

				std::string shaderfileStr = ShaderPackageFile::GetShaderFileTypeName(kv.first);
				GLenum openglShaderType = ConvertShaderFileTypeToGLenum(kv.first);
				const std::string& shaderSource = kv.second;

				// Create an empty shader handle
				GLuint shaderCode = glCreateShader(openglShaderType);

				// Send the shader source code to GL
				// Note that std::string's .c_str is NULL character terminated.
				const GLchar* source = shaderSource.c_str();
				glShaderSource(shaderCode, 1, &source, 0);

				// Compile the vertex shader
				glCompileShader(shaderCode);

				GLint isCompiled = 0;
				glGetShaderiv(shaderCode, GL_COMPILE_STATUS, &isCompiled);
				if (isCompiled == GL_FALSE)
				{
					GLint maxLength = 0;
					glGetShaderiv(shaderCode, GL_INFO_LOG_LENGTH, &maxLength);

					// The maxLength includes the NULL character
					std::vector<GLchar> infoLog(maxLength);
					glGetShaderInfoLog(shaderCode, maxLength, &maxLength, &infoLog[0]);

					// We don't need the shader anymore.
					glDeleteShader(shaderCode);

					MAB_CORE_ERROR("{0} error: {1}", shaderfileStr, infoLog.data());
					std::string logMessage = shaderfileStr + " shader compilation failure!";
					MAB_CORE_ASSERT(false, logMessage);
					break;
				}

				// Attach our shader to our program
				glAttachShader(program, shaderCode);
				glShaderIDs.push_back(shaderCode);

			}

			// Link our program
			glLinkProgram(program);

			// Note the different functions here: glGetProgram* instead of glGetShader*.
			GLint isLinked = 0;
			glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
			if (isLinked == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

				// We don't need the program anymore.
				glDeleteProgram(program);

				// We don't neet the shaders also.
				for (auto id : glShaderIDs) {
					glDeleteShader(id);
				}

				MAB_CORE_ERROR("{0}", infoLog.data());
				MAB_CORE_ASSERT(false, "Shader link failure!");
				return;
			}

			// Always detach shaders after a successful link.
			for (auto id : glShaderIDs) {
				glDetachShader(program, id);
			}

			// The last thing that we have to set
			m_RendererId = program;
		}

		void OpenGLShader::UploadUniformInt(const std::string& name, int value)
		{
			GLint location = glGetUniformLocation(m_RendererId, name.c_str());
			glUniform1i(location, value);
		}

		void OpenGLShader::UploadUniformInt2(const std::string& name, const glm::ivec2& value)
		{
			GLint location = glGetUniformLocation(m_RendererId, name.c_str());
			glUniform2i(location, value.x, value.y);
		}

		void OpenGLShader::UploadUniformInt3(const std::string& name, const glm::ivec3& value)
		{
			GLint location = glGetUniformLocation(m_RendererId, name.c_str());
			glUniform3i(location, value.x, value.y, value.z);
		}

		void OpenGLShader::UploadUniformInt4(const std::string& name, const glm::ivec4& value)
		{
			GLint location = glGetUniformLocation(m_RendererId, name.c_str());
			glUniform4i(location, value.x, value.y, value.z, value.w);
		}

		void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
		{
			GLint location = glGetUniformLocation(m_RendererId, name.c_str());
			glUniform1f(location, value);
		}

		void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
		{
			GLint location = glGetUniformLocation(m_RendererId, name.c_str());
			glUniform2f(location, value.x, value.y);
		}

		void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
		{
			GLint location = glGetUniformLocation(m_RendererId, name.c_str());
			glUniform3f(location, value.x, value.y, value.z);
		}

		void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
		{
			GLint location = glGetUniformLocation(m_RendererId, name.c_str());
			glUniform4f(location, value.x, value.y, value.z, value.w);
		}

		void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
		{
			GLint location = glGetUniformLocation(m_RendererId, name.c_str());
			glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
		}

		void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
		{
			GLint location = glGetUniformLocation(m_RendererId, name.c_str());
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
		}

	}
}