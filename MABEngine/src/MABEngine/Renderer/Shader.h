#pragma once

#include "MABEngine/Core.h"
#include "MABEngine/Renderer/ShaderPackageFile.h"

#include <string>


namespace MABEngine {
	namespace Renderer {
		
		class MABENGINE_API Shader {
		public:
			virtual ~Shader() = default;

			virtual void Bind() const = 0;
			virtual void UnBind() const = 0;

			virtual const std::string& GetName() const = 0;

			static Ref<Shader> Create(const ShaderPackageFile& packageInfo);
			static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		};

	}
}
