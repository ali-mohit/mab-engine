#pragma once

#include "MABEngine/Core.h"

#include <string>
#include <glm/glm.hpp>

namespace MABEngine {
	namespace Renderer {
		
		class MABENGINE_API Shader {
		public:
			Shader(const std::string& vertextSource, const std::string fragmentSource);
			~Shader();

			void Bind();
			void UnBind();

			uint32_t GetRendererId() { return m_RendererId; }

			void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		private:
			uint32_t m_RendererId;
		};

	}
}
