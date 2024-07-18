#pragma once

#include <MABEngine.h>
#include <glm/glm.hpp>

#include "Tools/ParticleProps.h"
#include "Tools/ParticleSystem.h"

namespace SimpleGame {
	class Player {
	public:
		Player();
		void LoadAssets();

		void OnUpdate(MABEngine::Core::EngineTimeStep ts);
		void OnRender();

		void OnImGuiRender();

		void Reset();

		float GetRotation() { return m_Velocity.y * 4.0f - 90.0f; }
		const glm::vec2& GetScaleTexture() const { return m_ScaleTexture; }
		const glm::vec2& GetPosition() const { return m_Position; }

		uint32_t GetScore() const { return (uint32_t)(m_Position.x + 10.f) / 10.0f; }
	private:
		glm::vec2 m_Position = { -10.0f, 0.0f };
		glm::vec2 m_Velocity = { 5.0f, 0.0f };
		glm::vec2 m_ScaleTexture = { 1.0f, 1.6f };

		float m_EnginePower = 0.5f;
		float m_Gravity = 0.4f;

		float m_Time = 0.0f;
		float m_SmokeEmitInterval = 0.4f;
		float m_SmokeNextEmitTime = m_SmokeEmitInterval;

		Tools::ParticleProps m_SmokeParticle;
		Tools::ParticleProps m_EngineParticle;
		Tools::ParticleSystem m_ParticleSystem;

		MABEngine::Core::Ref<MABEngine::Textures::Texture2D> m_ShipTextuer;

	};
}
