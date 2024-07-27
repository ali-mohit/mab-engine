#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/GraphicContext.h"
#include "MABEngine/Renderer/GraphicCardInfo.h"

struct GLFWwindow;

namespace MABEngine {
	namespace Renderer {

		class MABENGINE_API OpenGLGraphicContext : public GraphicContext {
		public:
			OpenGLGraphicContext(GLFWwindow* windowHandle, Core::Ref<GraphicCardInfo> graphicCardInfo);

			virtual void Init() override;
			virtual void SwapBuffers() override;

			virtual const Core::Ref<GraphicCardInfo> GetGraphicCardInfo() const override { return m_GraphicCardInfo; }
		private:
			GLFWwindow* m_WindowHandle;
			Core::Ref<GraphicCardInfo> m_GraphicCardInfo;
		};

	}
}