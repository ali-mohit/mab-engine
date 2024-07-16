#include <mabengine_pch.h>
#include <MABEngine.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include "Tools/ParticleSystem.h"
#include "Tools/ParticleProps.h"
#include "Utilities/Random.h"

namespace Tools {
	
	ParticleSystem::ParticleSystem()
	{
		m_ParticlePool.resize(1000);
	}
	
	void ParticleSystem::Emit(const ParticleProps& particleProp)
	{
		ParticleInfo& particle = m_ParticlePool[m_PoolIndex];

		particle.IsActive = true;
		particle.Position = particleProp.Position;
		particle.Rotation = Utilities::Random::Float() * 2.0f * glm::pi<float>();

		// Velocity
		particle.Velocity = particleProp.Velocity;
		particle.Velocity.x += particleProp.VelocityVariation.x * (Utilities::Random::Float() - 0.5f);
		particle.Velocity.y += particleProp.VelocityVariation.y * (Utilities::Random::Float() - 0.5f);

		// Color
		particle.ColorBegin = particleProp.ColorBegin;
		particle.ColorEnd = particleProp.ColorEnd;

		// Size
		particle.SizeBegin = particleProp.SizeBegin + particleProp.SizeVariation * (Utilities::Random::Float() - 0.5f);
		particle.SizeEnd = particleProp.SizeEnd;

		// Life
		particle.LifeTime = particleProp.LifeTime;
		particle.LifeRemain = particleProp.LifeTime;

		m_PoolIndex -= 1;
		m_PoolIndex = m_PoolIndex % m_ParticlePool.size();

	}
	
	void ParticleSystem::OnUpdate(MABEngine::Core::EngineTimeStep ts)
	{
		for (auto& particle : m_ParticlePool) {
			if (!particle.IsActive)
				continue;

			if (particle.LifeRemain <= 0.0) {
				particle.IsActive = false;
				continue;
			}

			particle.LifeRemain -= ts;
			particle.Position += particle.Velocity * (float)ts;
			particle.Rotation += 0.1f * ts;
		}
	}
	
	void ParticleSystem::OnRender()
	{
		for (auto& particle : m_ParticlePool) {
			if (!particle.IsActive)
				continue;

			float life = particle.LifeRemain / particle.LifeTime;
			glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
			color.a = color.a * life;

			float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);
			MABEngine::Renderer::EngineRenderer2d::DrawQuad(
				{ particle.Position.x, particle.Position.y, -0.05 },
				{ size, size },
				glm::radians(particle.Rotation),
				color
			);
		}
	}
}