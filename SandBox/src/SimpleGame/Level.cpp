#include "mabengine_pch.h"

#include "SimpleGame/Level.h"
#include "Utilities/HSV.h"
#include "Utilities/Random.h"

#include <MABEngine.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace SimpleGame {
	void Level::Init()
	{
		m_TriangleTexture = MABEngine::Textures::Texture2D::Create("assets/simple_game/images/Triangles.png");
		m_Player.LoadAssets();

		m_PillarList.resize(5);
		for (int i = 0; i < 5; i++) {
			CreatePillar(i, i * 10.0f);
		}
	}
	
	void Level::OnUpdate(MABEngine::Core::EngineTimeStep ts)
	{
		m_Player.OnUpdate(ts);

		if (CollisionTest()) {
			GameOver();
			return;
		}

		m_PillarHSV.x += 0.1f * ts;
		if (m_PillarHSV.x > 1.0f)
			m_PillarHSV.x = 0.0f;

		if (m_Player.GetPosition().x > m_PillarTarget) {
			CreatePillar(m_PillarIndex, m_PillarTarget + 20.0f);
			m_PillarIndex += 1;
			m_PillarIndex = m_PillarIndex % m_PillarList.size();
			m_PillarTarget += 10.0f;
		}
	}

	void Level::OnRender()
	{
		const auto& playerPos = m_Player.GetPosition();
		
		glm::vec4 color = Utilities::HSVtoRGB(m_PillarHSV);

		//background
		MABEngine::Renderer::EngineRenderer2d::DrawQuad(
			{ playerPos.x, 0.0f, -0.8f },
			{ 50.0f, 50.0f },
			{ 0.3f, 0.3f, 0.3f, 1.0f}
		);

		// Floor and Ceiling 
		MABEngine::Renderer::EngineRenderer2d::DrawQuad(
			{ playerPos.x , 34.0f },
			{ 50.0f, 50.0f },
			color
		);
		MABEngine::Renderer::EngineRenderer2d::DrawQuad(
			{ playerPos.x , -34.0f },
			{ 50.0f, 50.0f },
			color
		);

		for (auto& pillar : m_PillarList) {
			MABEngine::Renderer::EngineRenderer2d::DrawQuad(
				pillar.TopPosition,
				pillar.TopScale,
				glm::radians(180.0f),
				m_TriangleTexture,
				color
			);

			MABEngine::Renderer::EngineRenderer2d::DrawQuad(
				pillar.BottomPosition,
				pillar.BottomScale,
				glm::radians(0.0f),
				m_TriangleTexture,
				color
			);
		}

		m_Player.OnRender();
	}
	
	void Level::OnImGuiRender()
	{
		m_Player.OnImGuiRender();
	}
	
	void Level::CreatePillar(int index, float offset)
	{
		PillarInfo& pillar = m_PillarList[index];
		pillar.TopPosition.x = offset;
		pillar.BottomPosition.x = offset;
		pillar.TopPosition.z = (index * 0.1f - 0.5f) - 0.1;
		pillar.BottomPosition.z = (index * 0.1f - 0.5f + 0.05f) - 0.1;

		float center = Utilities::Random::Float() * 35.0f - 17.5f;
		float gap = 3.0f + Utilities::Random::Float() * 5.0f;

		pillar.TopPosition.y = 10.0f - ((10.0f - center) * 0.2f) + gap * 0.5f;
		pillar.BottomPosition.y = -10.0f - ((-10.0f - center) * 0.2f) - gap * 0.5f;
	}
	
	
	
	bool Level::CollisionTest()
	{
		if (glm::abs(m_Player.GetPosition().y) > 8.5f)
			return true;

		glm::vec4 playerGrid[4] = {
			{ -0.5f, -0.5f, 0.0f, 1.0f},
			{  0.5f, -0.5f, 0.0f, 1.0f},
			{  0.5f,  0.5f, 0.0f, 1.0f},
			{ -0.5f,  0.5f, 0.0f, 1.0f}
		};

		glm::vec4 triangleGrid[3] = {
			{ -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
			{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
			{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
		};

		const auto& playerPos = m_Player.GetPosition();
		glm::vec4 playerGridTransform[4];

		for (int i = 0; i < 4; i++) {
			playerGridTransform[i] = glm::translate(glm::mat4(1.0f), { playerPos.x, playerPos.y, 0.0 })
				* glm::rotate(glm::mat4(1.0f), glm::radians(m_Player.GetRotation()), {0.0f, 0.0f, 1.0f})
				* glm::scale(glm::mat4(1.0f), { m_Player.GetScaleTexture() , 1.0f})
				* playerGrid[i];
		}

		for (auto& pillar : m_PillarList) {
			glm::vec2 triangleGridTransform[3];

			//Top Pillar
			for (int i = 0; i < 3; i++) {
				triangleGridTransform[i] = glm::translate(glm::mat4(1.0f), { pillar.TopPosition.x, pillar.TopPosition.y, 0.0 })
					* glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), { 0.0f, 0.0f, 1.0f })
					* glm::scale(glm::mat4(1.0f), { pillar.TopScale.x, pillar.TopScale.y , 1.0f })
					* triangleGrid[i];
			}

			for (auto& vertex : playerGridTransform) {
				if (IsPointInTriangle({ vertex.x, vertex.y }, triangleGridTransform[0], triangleGridTransform[1], triangleGridTransform[2]))
					return true;
			}

			//Bottom Pillar
			for (int i = 0; i < 3; i++) {
				triangleGridTransform[i] = glm::translate(glm::mat4(1.0f), { pillar.BottomPosition.x, pillar.BottomPosition.y, 0.0 })
					* glm::scale(glm::mat4(1.0f), { pillar.BottomScale.x, pillar.BottomScale.y , 1.0f })
					* triangleGrid[i];
			}

			for (auto& vertex : playerGridTransform) {
				if (IsPointInTriangle({ vertex.x, vertex.y }, triangleGridTransform[0], triangleGridTransform[1], triangleGridTransform[2]))
					return true;
			}

		}

		return false;
	}
	
	void Level::GameOver()
	{
		m_GameOver = true;
	}

	bool Level::IsPointInTriangle(const glm::vec2& p, const glm::vec2& t0, const glm::vec2& t1, const glm::vec2& t2)
	{
		float s = t0.y * t2.x - t0.x * t2.y + (t2.y - t0.y) * p.x + (t0.x - t2.x) * p.y;
		float t = t0.x * t1.y - t0.y * t1.x + (t0.y - t1.y) * p.x + (t1.x - t0.x) * p.y;

		if ((s < 0) != (t < 0))
			return false;

		float A = -t1.y * t2.x + t0.y * (t2.x - t1.x) + t0.x * (t1.y - t2.y) + t1.x * t2.y;

		return A < 0 ?
			(s <= 0 && s + t >= A) :
			(s >= 0 && s + t <= A);
	}
	
	void Level::Reset()
	{
		m_GameOver = false;

		m_Player.Reset();

		m_PillarTarget = 30.0f;
		m_PillarIndex = 0;
		for (int i = 0; i < 5; i++) {
			CreatePillar(i, i * 10.0f);
		}
	}
}

