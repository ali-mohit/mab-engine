#include "mabengine_pch.h"
#include "SimpleGame/Player.h"

#include <MABEngine.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>


namespace SimpleGame {
	Player::Player()
	{
		//Smoke
		m_SmokeParticle.Position = { 0.0f, 0.0f };
		
		m_SmokeParticle.Velocity = { -3.0f, 0.0f };
		m_SmokeParticle.VelocityVariation = { 4.0f, 2.0f };
		
		m_SmokeParticle.SizeBegin = 0.35f;
		m_SmokeParticle.SizeEnd = 0.0f;
		m_SmokeParticle.SizeVariation = 0.15f;
		
		m_SmokeParticle.ColorBegin = { 0.8f, 0.8f, 0.8f, 1.0f };
		m_SmokeParticle.ColorEnd = { 0.6f, 0.6f, 0.6f, 1.0f };
		
		m_SmokeParticle.LifeTime = 6.0f;

		// Flames
		m_EngineParticle.Position = { 0.0f, 0.0f };

		m_EngineParticle.Velocity = { -3.0f, 0.0f };
		m_EngineParticle.VelocityVariation = { 3.0f, 1.0f };
		
		m_EngineParticle.SizeBegin = 0.5f;
		m_EngineParticle.SizeEnd = 0.0f;
		m_EngineParticle.SizeVariation = 0.3f;
		
		m_EngineParticle.ColorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
		m_EngineParticle.ColorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f , 1.0f };
		
		m_EngineParticle.LifeTime = 3.0f;
	}
	
	void Player::LoadAssets()
	{
		m_ShipTextuer = MABEngine::Textures::Texture2D::Create("assets/simple_game/images/ShipTexture.png");
	}

	void Player::OnUpdate(MABEngine::Core::EngineTimeStep ts)
	{
		m_Time += ts;

		if (MABEngine::Inputs::Input::IsKeyPressed(MABEngine::Inputs::MABKeyboardCode::Mab_Key_Space)) {
			m_Velocity.y += m_EnginePower;
			if (m_Velocity.y < 0.0f) {
				m_Velocity.y += m_EnginePower * 2.0f;
			}

			// Flames
			glm::vec2 emissionPoint = { 0.0f, -0.6f };
			float rotation = glm::radians(GetRotation());
			glm::vec4 rotated = glm::rotate(glm::mat4(1.0f),rotation, { 0.0f, 0.0f, 1.0f }) * glm::vec4(emissionPoint, 0.0f, 1.0f);
			m_EngineParticle.Position = m_Position + glm::vec2{ rotated.x, rotated.y };
			m_EngineParticle.Velocity.y = -m_Velocity.y * 0.2f - 0.2f;
			m_ParticleSystem.Emit(m_EngineParticle);
		}
		else {
			m_Velocity.y -= m_Gravity;
		}

		m_Velocity.y = glm::clamp(m_Velocity.y, -20.0f, 20.0f);
		m_Position += m_Velocity * (float)ts;

		// Particles
		if (m_Time > m_SmokeNextEmitTime)
		{
			m_SmokeParticle.Position = m_Position;
			m_ParticleSystem.Emit(m_SmokeParticle);
			m_SmokeNextEmitTime += m_SmokeEmitInterval;
		}

		m_ParticleSystem.OnUpdate(ts);
	}

	void Player::OnRender()
	{
		m_ParticleSystem.OnRender();

		MABEngine::Renderer::EngineRenderer2d::DrawQuad(
			{ m_Position.x, m_Position.y, 0.5f },
			GetScaleTexture(),
			glm::radians(GetRotation()),
			m_ShipTextuer
		);
	}
	void Player::OnImGuiRender()
	{
		ImGui::DragFloat("Engine Power", &m_EnginePower, 0.1f);
		ImGui::DragFloat("Gravity", &m_Gravity, 0.1f);

		std::string message = "Position: {" + std::to_string(m_Position.x) + ", " + std::to_string(m_Position.y) + "} ";
		ImGui::Text(message.c_str());
	}
	void Player::Reset()
	{
		m_Position = { -10.0f, 0.0f };
		m_Velocity = { 5.0f, 0.0f };
	}
}