#pragma once

#include <MABEngine.h>

#include "SimpleGame/Player.h"
#include "SimpleGame/Pillar.h"

namespace SimpleGame {
	class Level {
	public:
		void Init();

		void OnUpdate(MABEngine::Core::EngineTimeStep ts);
		void OnRender();
		void OnImGuiRender();

		bool IsGameOver() const { return m_GameOver; }
		void Reset();

		const Player& GetPlayer() const { return m_Player; }
	private:
		void CreatePillar(int index, float offset);
		bool CollisionTest();

		void GameOver();

		bool IsPointInTriangle(const glm::vec2& p, const glm::vec2& t1, const glm::vec2& t2, const glm::vec2& t3);
	private:
		Player m_Player;

		bool m_GameOver = false;

		float m_PillarTarget = 30.0f;
		int m_PillarIndex = 0;

		glm::vec3 m_PillarHSV = { 0.0f, 0.8f, 0.8f };

		std::vector<PillarInfo> m_PillarList;
		MABEngine::Core::Ref<MABEngine::Textures::Texture2D> m_TriangleTexture;
	};
}