#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/Shader.h"
#include "MABEngine/Renderer/ShaderPackageFile.h"

#include <unordered_map>


namespace MABEngine {
	namespace Renderer {

		class MABENGINE_API ShaderLibrary {
		public:
			ShaderLibrary();
			~ShaderLibrary();

			void AddShader(const Core::Ref<Shader>& shader);
			void AddShader(const std::string& name, const Core::Ref<Shader>& shader);
			Core::Ref<Shader> Load(const ShaderPackageFile& info);
			Core::Ref<Shader> Load(const std::string& name, const std::string& vertextShaderCode, const std::string& fragmentShaderCode);

			Core::Ref<Shader> GetShader(const std::string& name);

			bool ShaderExists(const std::string& name) { return m_ShaderRepo.find(name) != m_ShaderRepo.end(); }

			void SetWarningFlagOff() { m_WarningFlag = 0; }
			void SetWarningFlagOn() { m_WarningFlag = 1; }
			uint32_t GetWarningFlag() { return m_WarningFlag; }

		private:
			std::unordered_map<std::string, Core::Ref<Shader>> m_ShaderRepo;
			uint32_t m_WarningFlag = 1;
		};
	}
}