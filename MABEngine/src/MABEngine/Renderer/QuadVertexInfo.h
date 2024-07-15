#pragma once

#include "glm/glm.hpp"

namespace MABEngine {

	namespace Renderer {

		struct QuadVertexInfo {
			glm::vec4 Position;
			glm::vec4 Color;
			glm::vec2 TextCoordinate;
			glm::vec2 Tiling = { 1.0f, 1.0f };
			float TextureId = 0;
			float TextureMaskId = 0;
			float TransformIndex = -1;
		};

	}
}