#include "mabengine_pch.h"

#include "MABEngine/Core.h"
#include "MABEngine/Logging/Log.h"
#include "Platform/OpenGL/Textures/OpenGLTexture2D.h"

#include "stb_image.h"
#include <glad/glad.h>

namespace MABEngine {
	namespace Textures {
		OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
			:m_Path(path), m_Width(0), m_Height(0), m_RendererId(0), m_Channels(0)
		{
			int width, height, channels = 0;
			stbi_set_flip_vertically_on_load(1);
			stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

			MAB_CORE_ASSERT(data, "Failed to load image!");

			m_Width = width;
			m_Height = height;
			m_Channels = channels;

			GLenum internalFormat = getInternalGLFormat();
			GLenum dataFormat = getDataGLFormat();

			MAB_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
			glTextureStorage2D(m_RendererId, 1, internalFormat, m_Width, m_Height);

			glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

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

		GLenum OpenGLTexture2D::getInternalGLFormat() const
		{
			switch (m_Channels) {
			case 1: return GL_R8;
			case 2: return GL_RG8;
			case 3: return GL_RGB8;
			case 4: return GL_RGBA8;
			default: return 0; // Default to GL_RGBA for safety
			}
		}

		GLenum OpenGLTexture2D::getDataGLFormat() const
		{
			switch (m_Channels) {
			case 1: return GL_RED;
			case 2: return GL_RG;
			case 3: return GL_RGB;
			case 4: return GL_RGBA;
			default: return 0; // Default to GL_RGBA for safety
			}
		}
	}
}