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

		void OpenGLRendererAPI::DrawIndexed(const Core::Ref<VertexArray>& vertextArray)
		{
			glDrawElements(GL_TRIANGLES, vertextArray->GetIndexBufferList()[0]->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
	}
}