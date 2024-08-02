#include "mabengine_pch.h"

#include "MABEngine/Core/Base.h"
#include "MABEngine/Logging/Log.h"
#include "Platform/OpenGL/Textures/OpenGLTexture2D.h"

#include "stb_image.h"
#include <glad/glad.h>

namespace MABEngine {
	namespace Textures {

		OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
			:m_Path(""), m_Width(width), m_Height(height), m_RendererId(0), m_Channels(4)
		{
			MAB_PROFILE_FUNCTION();

			GLenum internalFormat = getInternalGLFormat();
			GLenum dataFormat = getDataGLFormat();

			MAB_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
			glTextureStorage2D(m_RendererId, 1, internalFormat, m_Width, m_Height);

			glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

		}

		OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
			:m_Path(path), m_Width(0), m_Height(0), m_RendererId(0), m_Channels(0)
		{
			MAB_PROFILE_FUNCTION();

			int width, height, channels = 0;
			stbi_set_flip_vertically_on_load(1);
			stbi_uc* data = nullptr;
			{
				MAB_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
				data = stbi_load(path.c_str(), &width, &height, &channels, 0);
			}
			
			MAB_CORE_ASSERT(data, "Failed to load image!");

			m_Width = width;
			m_Height = height;
			m_Channels = channels;

			GLenum internalFormat = getInternalGLFormat();
			GLenum dataFormat = getDataGLFormat();

			MAB_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
			glTextureStorage2D(m_RendererId, 1, internalFormat, m_Width, m_Height);

			glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		OpenGLTexture2D::~OpenGLTexture2D() {
			MAB_PROFILE_FUNCTION();

			glDeleteTextures(1, &m_RendererId);
		}

		void OpenGLTexture2D::SetData(void* data, uint32_t size) {
			MAB_PROFILE_FUNCTION();

			MAB_CORE_ASSERT(size == m_Width * m_Height * m_Channels, "Data must be entire texture (the size is not correct)!");

			GLenum dataFormat = getDataGLFormat();
			glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		}

		void OpenGLTexture2D::Bind(uint32_t slot)
		{
			MAB_PROFILE_FUNCTION();

			glBindTextureUnit(slot, m_RendererId);
		}

		void OpenGLTexture2D::UnBind()
		{
			MAB_PROFILE_FUNCTION();

			glBindTexture(GL_TEXTURE_2D, 0);
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