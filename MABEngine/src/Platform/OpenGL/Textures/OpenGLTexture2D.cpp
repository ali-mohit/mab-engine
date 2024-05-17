#include "mabengine_pch.h"

#include "MABEngine/Core.h"
#include "MABEngine/Logging/Log.h"
#include "Platform/OpenGL/Textures/OpenGLTexture2D.h"

#include "stb_image.h"
#include <glad/glad.h>

namespace MABEngine {
	namespace Textures {
		OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
			:m_Path(path)
		{
			int width, height, channels = 0;
			stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

			MAB_CORE_ASSERT(data, "Failed to load image!");

			m_Width = width;
			m_Height = height;

			m_Channels = channels;

			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
			glTextureStorage2D(m_RendererId, 1, GL_RGB8, m_Width, m_Height);

			glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}

		OpenGLTexture2D::~OpenGLTexture2D()
		{
			glDeleteTextures(1, &m_RendererId);
		}

		void OpenGLTexture2D::Bind(uint32_t slot)
		{
			glBindTextureUnit(slot, m_RendererId);
		}
	}
}