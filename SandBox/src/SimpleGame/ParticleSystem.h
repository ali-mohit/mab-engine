#pragma once

#include <MABEngine.h>
#include <glm/glm.hpp>

#include "SimpleGame/ParticleProps.h"

namespace SimpleGame {

	class MABENGINE_API ParticleSystem {
	public:
		ParticleSystem();

		void Emit(const ParticleProps& particleProps);

		void OnUpdate(MABEngine::Core::EngineTimeStep ts);
		void OnRender();
	private:
		struct ParticleInfo {
			glm::vec2 Position;
			glm::vec2 Velocity;

			glm::vec4 ColorBegin;
			glm::vec4 ColorEnd;

			float Rotation = 0.0f;

			float SizeBegin;
			float SizeEnd;

			float LifeTime = 1.0f;
			float LifeRemain = 0.0f;

			bool IsActive = false;
		};

		std::vector<ParticleInfo> m_ParticlePool;
		uint32_t m_PoolIndex = 999;
	};

}