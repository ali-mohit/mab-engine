#include "mabengine_pch.h"
#include "MABEngine/Core.h"
#include "MABEngine/Logging/Log.h"

#include "MABEngine/Renderer/ShaderLibrary.h"
#include "MABEngine/Renderer/Shader.h"

namespace MABEngine {
	namespace Renderer {
		ShaderLibrary::ShaderLibrary()
		{
		}

		ShaderLibrary::~ShaderLibrary()
		{
		}

		void ShaderLibrary::AddShader(const Ref<Shader>& shader)
		{
			auto& name = shader->GetName();
			AddShader(name, shader);
		}

		void ShaderLibrary::AddShader(const std::string& name, const Ref<Shader>& shader)
		{
			if (ShaderExists(name) && m_WarningFlag)
				MAB_CORE_WARN("Shader {0} exists! so, it is updated", name);

			m_ShaderRepo[name] = shader;
		}

		Ref<Shader> ShaderLibrary::Load(const ShaderPackageFile& packageInfo)
		{
			auto newShader = Shader::Create(packageInfo);

			AddShader(newShader);
			return newShader;
		}

		Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertextShaderCode, const std::string& fragmentShaderCode)
		{
			auto newShader = Shader::Create(name, vertextShaderCode, fragmentShaderCode);

			AddShader(newShader);
			return newShader;
		}

		Ref<Shader> ShaderLibrary::GetShader(const std::string& name)
		{
			MAB_CORE_ASSERT(ShaderExists(name), "The shader does not exist");

			return m_ShaderRepo[name];
		}
	}
}