#pragma once

#include "MABEngine/Core/Base.h"

#include <string>
#include <glm/glm.hpp>

namespace MABEngine {
	namespace Components {

		struct TextComponent
		{
			std::string TextString;
			glm::vec4 Color{ 1.0f };
			float Kerning = 0.0f;
			float LineSpacing = 0.0f;

			TextComponent() = default;
			TextComponent(const TextComponent& other) = default;
		};
	}

}
