#pragma once
#include "MABEngine/Core/Base.h"
#include "MABEngine/Textures/Texture2D.h"
#include "MABEngine/Textures/SubTexture2D.h"

#include <glm/glm.hpp>

namespace MABEngine {
	namespace Components {
		struct MABENGINE_API SpriteRendererComponent {

			glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
			Core::Ref<Textures::Texture2D> Texture2D;
			Core::Ref<Textures::SubTexture2D> SubTexture;
			glm::vec2 Tiling = { 1.0f, 1.0f };

			SpriteRendererComponent() = default;
			SpriteRendererComponent(const SpriteRendererComponent& other) = default;
			SpriteRendererComponent(
				const glm::vec4& color,
				Core::Ref<Textures::Texture2D> texture2d = nullptr,
				Core::Ref<Textures::SubTexture2D> subTexture2d = nullptr,
				glm::vec2 tiling = { 1.0f, 1.0f}
			) : Color(color),
				Texture2D(texture2d),
				SubTexture(subTexture2d),
				Tiling(tiling) {}

		};
	}
}
