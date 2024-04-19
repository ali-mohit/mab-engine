#pragma once

#include "MABEngine/Core.h"

#include <string>

namespace MABEngine {
	namespace Renderer {
		
		class MABENGINE_API Shader {
		public:
			Shader(const std::string& vertextSource, const std::string fragmentSource);
			~Shader();

			void Bind();
			void UnBind();

			uint32_t GetRendererId() { return m_RendererId; }

		private:
			uint32_t m_RendererId;
		};

	}
}
