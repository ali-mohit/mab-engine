#pragma once

#include "MABEngine/Core.h"
#include "MABEngine/Textures/Texture2D.h"

namespace MABEngine {
	namespace Textures {
		
		class MABENGINE_API OpenGLTexture2D : public Texture2D {
		public:
			OpenGLTexture2D(const std::string& path);
			~OpenGLTexture2D();

			virtual uint32_t GetWidth() const override { return m_Width; };
			virtual uint32_t GetHeight() const override { return m_Height; };

			virtual uint32_t GetRendererId() const override { return m_RendererId; };
			virtual uint32_t GetChannels() const override { return m_Channels; };

			virtual void Bind(uint32_t slot = 0) override;

		private:
			//GLenum getGLFormat() const;
			unsigned int getInternalGLFormat() const;
			unsigned int getDataGLFormat() const;
		private:
			std::string m_Path;
			uint32_t m_Width;
			uint32_t m_Height;
			uint32_t m_RendererId;
			uint32_t m_Channels;
		};
	}
}