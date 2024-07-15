#include "mabengine_pch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace MABEngine {

	namespace Renderer {
		void OpenGLRendererAPI::Init()
		{
			MAB_PROFILE_FUNCTION();

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);
		}
		
		uint32_t OpenGLRendererAPI::GetMaxNumberOfTextureImageUnit()
		{
			GLint maxTextureUnit = 0;
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnit);
			return maxTextureUnit;
		}

		void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.b, color.g, color.a);
		}

		void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			glViewport(x, y, width, height);
		}
		
		void OpenGLRendererAPI::Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void OpenGLRendererAPI::DrawIndexed(const Core::Ref<VertexArray>& vertextArray, uint32_t indexCount)
		{
			uint32_t count = indexCount > 0 ? indexCount : vertextArray->GetIndexBuffer()->GetCount();

			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		}
	}
}