#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/GraphicCardInfo.h"

#include <string>

namespace MABEngine {
	namespace Renderer {
		class MABENGINE_API OpenGLGraphicCardInfo: public GraphicCardInfo {
		public:
			OpenGLGraphicCardInfo();
			~OpenGLGraphicCardInfo();

			virtual std::string GetGraphicCardVendor() override;
			virtual std::string GetGraphicCardRenderer() override;
			virtual uint32_t GetMaxNumberOfTextureImageUnit() override;
			virtual std::string GetOpenGLVersion() override;
			virtual uint32_t GetMaxFrameBufferSize() override;
		
		private:
			std::string m_GraphicCardVendor = "";
			std::string m_GraphicCardRenderer = "";
			std::string m_OpenGLVersion = "";
		};
	}
}