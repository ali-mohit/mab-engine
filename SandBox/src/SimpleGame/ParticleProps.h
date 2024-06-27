#pragma once

#include <glm/glm.hpp>

namespace SimpleGame {
	struct ParticleProps {
		glm::vec2 Position;
		glm::vec2 Velocity;
		glm::vec2 VelocityVariation;
		glm::vec4 ColorBegin;
		glm::vec4 ColorEnd;
		float SizeBegin;
		float SizeEnd;
		float SizeVariation;
		float LifeTime = 1.0f;
	};

}