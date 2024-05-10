#pragma once

#include "MABEngine/Core.h"

#include <string>


namespace MABEngine {
	namespace Renderer {
		
		class MABENGINE_API Shader {
		public:
			virtual ~Shader() = default;

			virtual void Bind() const = 0;
			virtual void UnBind() const = 0;

			static Shader* Create(const std::string& vertexSource, const std::string fragmentSource);
		};

	}
}
