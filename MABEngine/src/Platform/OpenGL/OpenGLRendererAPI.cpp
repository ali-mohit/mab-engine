#include "mabengine_pch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace MABEngine {

	namespace Renderer {
		
		void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.b, color.g, color.a);
		}
		
		void OpenGLRendererAPI::Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertextArray)
		{
			glDrawElements(GL_TRIANGLES, vertextArray->GetIndexBufferList()[0]->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
	}
}