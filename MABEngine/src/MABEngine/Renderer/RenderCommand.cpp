#include "mabengine_pch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/Renderer/OpenGLRendererAPI.h"

namespace MABEngine {

	namespace Renderer {
		RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
	}
}