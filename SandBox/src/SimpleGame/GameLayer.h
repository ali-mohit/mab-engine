#pragma once

#include <MABEngine.h>
#include <glm/glm.hpp>
#include <imgui.h>

#include "SimpleGame/Level.h"

namespace SimpleGame {

	class GameLayer : public MABEngine::Layers::Layer {
	public:
		GameLayer(uint32_t width, uint32_t height);
		virtual ~GameLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(MABEngine::Core::EngineTimeStep ts) override;
		virtual void OnImGuiRender() override;

		void OnEvent(MABEngine::Events::Event& event) override;
	private:
		void CreateCamera();
		bool OnWindowsResize(MABEngine::Events::WindowResizeEvent& e);
		bool OnMouseButtonPressed(MABEngine::Events::MouseButtonPressedEvent& e);
		bool OnKeyboardButtonPressed(MABEngine::Events::KeyPressedEvent& e);
	private:
		uint32_t m_Width;
		uint32_t m_Height;
		MABEngine::Core::Scope<MABEngine::Camera::OrthographicCamera> m_Camera;
		Level m_Level;

		ImFont* m_Font = nullptr;
		float m_Time = 0.0f;
		bool m_Blink = false;

		enum class GameState {
			Play = 0,
			MainMenu = 1,
			GameOver = 2
		};

		GameState m_State = GameState::MainMenu;
	};

}
