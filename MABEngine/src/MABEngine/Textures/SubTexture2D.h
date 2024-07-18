#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Textures/Texture2D.h"

#include <glm/glm.hpp>

namespace MABEngine {
	namespace Textures {
		class MABENGINE_API SubTexture2D {
		public:
			SubTexture2D(const Core::Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

			const Core::Ref<Texture2D> GetTexture() const { return m_Texture; }
			const glm::vec2* GetTextureCoordinrate() const { return m_TextureCoordinate; }

			static Core::Ref<SubTexture2D> CreateFromCoordinates(
				const Core::Ref<Texture2D>& texture,
				const glm::vec2& coords,
				const glm::vec2& cellSize = { 128, 128 },
				const glm::vec2& spriteSize = { 1, 1 }
			);
		private:
			Core::Ref<Texture2D> m_Texture;

			glm::vec2 m_TextureCoordinate[4];
 		};
	}
}
