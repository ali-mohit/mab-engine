#pragma once

#include "MABEngine/Core.h"
#include "MABEngine/Renderer/GraphicContext.h"

struct GLFWwindow;

namespace MABEngine {
	namespace Renderer {

		class MABENGINE_API OpenGLGraphicContext : public GraphicContext {
		public:
			OpenGLGraphicContext(GLFWwindow* windowHandle);

			virtual void Init() override;
			virtual void SwapBuffers() override;

			virtual std::string GetGraphicCardVendor() override;
			virtual std::string GetGraphicCardRenderer() override;
			virtual uint32_t GetMaxNumberOfTextureImageUnit() override;
			std::string GetOpenGLVersion();
		private:
			GLFWwindow* m_WindowHandle;
			std::string m_GraphicCardVendor;
			std::string m_GraphicCardRenderer;
			std::string m_OpenGLVersion;

		};

	}
}