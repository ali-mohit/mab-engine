#pragma once

#include "MABEngine/Core.h"
#include "MABEngine/Renderer/ShaderFileType.h"

#include <string>

namespace MABEngine {

	namespace Renderer {

		class MABENGINE_API ShaderPackageFile {
		public:
			ShaderPackageFile(const std::string& name, const std::string& path, const std::string& prefix = "");
			~ShaderPackageFile();

			inline const std::string& GetName() const { return m_Name; }
			inline void SetName(const std::string& name) { m_Name = name; }

			inline const std::string& GetPackagePath() const { return m_Path; }
			inline void SetPackagePath(const std::string& path) { m_Path = path; }


			inline const std::string& GetPrefix() const { return m_Prefix; }
			inline void SetPrefix(const std::string& prefix) { m_Prefix = prefix; }

			const std::string& GetShaderFilePath(ShaderFileType fileType) const;
			static std::string GetShaderFileTypeName(ShaderFileType fileType);
		private:
			const std::string& GetShaderFilePostFix() const;
		private:
			std::string m_Name;
			std::string m_Path;
			std::string m_Prefix;
		};
	}
}