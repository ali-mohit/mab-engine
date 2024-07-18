#include "mabengine_pch.h"
#include "MABEngine/Textures/SubTexture2D.h"

namespace MABEngine {
	namespace Textures {
		
		SubTexture2D::SubTexture2D(const Core::Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
			:m_Texture(texture)
		{
			m_TextureCoordinate[0] = { min.x, min.y };
			m_TextureCoordinate[1] = { max.x, min.y };
			m_TextureCoordinate[2] = { max.x, max.y };
			m_TextureCoordinate[3] = { min.x, max.y };
		}

		Core::Ref<SubTexture2D> SubTexture2D::CreateFromCoordinates(
			const Core::Ref<Texture2D>& texture,
			const glm::vec2& coords,
			const glm::vec2& cellSize,
			const glm::vec2& spriteSize
		)
		{
			glm::vec2 min = {
				(coords.x * cellSize.x) / texture->GetWidth(),
				(coords.y * cellSize.y) / texture->GetHeight()
			};
			glm::vec2 max = {
				((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(),
				((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight() 
			};
			return Core::CreateRef<SubTexture2D>(texture, min, max);
		}



	}
}