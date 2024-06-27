#include <mabengine_pch.h>
#include <imgui.h>

#include "GameLayer.h"
#include "Utilities/Random.h"

namespace SimpleGame {
	GameLayer::GameLayer(uint32_t width, uint32_t height) 
		:Layer("SimpleGame"),
		m_Width(width),
		m_Height(height)
	{
		CreateCamera();

		Utilities::Random::Init();
	}

	void GameLayer::OnAttach()
	{
		m_Level.Init();

		ImGuiIO io = ImGui::GetIO();
		m_Font = io.Fonts->AddFontFromFileTTF("assets/simple_game/fonts/OpenSans-Regular.ttf", 120.0f);
	}

	void GameLayer::OnDetach()
	{
	}

	void GameLayer::OnUpdate(MABEngine::Core::EngineTimeStep ts)
	{
		m_Time += ts;

		if ((int)(m_Time * 10.0f) % 8 > 4)
			m_Blink = !m_Blink;

		if (m_Level.IsGameOver())
			m_State = GameState::GameOver;

		const auto& playerPosition = m_Level.GetPlayer().GetPosition();
		const auto& cameraPosition = m_Camera->GetPosition();
		m_Camera->SetPosition({ playerPosition.x, cameraPosition.y, 0.0f });

		switch (m_State)
		{
		case SimpleGame::GameLayer::GameState::Play:
			m_Level.OnUpdate(ts);
			break;
		case SimpleGame::GameLayer::GameState::MainMenu:
			break;
		case SimpleGame::GameLayer::GameState::GameOver:
			break;
		default:
			break;
		}

		

		MABEngine::Renderer::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		MABEngine::Renderer::RenderCommand::Clear();

		MABEngine::Renderer::EngineRenderer2d::BeginScene(*m_Camera);
		m_Level.OnRender();
		MABEngine::Renderer::EngineRenderer2d::EndScene();

	}

	void GameLayer::OnImGuiRender()
	{
		switch (m_State)
		{
		case SimpleGame::GameLayer::GameState::Play:
		{
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
			break;
		}
		case SimpleGame::GameLayer::GameState::MainMenu:
		{
			auto pos = ImGui::GetWindowPos();
			pos.x += m_Width * 0.5f - 300.0f;
			pos.y += 50.0f;

			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
			break;
		}
		case SimpleGame::GameLayer::GameState::GameOver:
		{
			auto pos = ImGui::GetWindowPos();
			pos.x += m_Width * 0.5f - 300.0f;
			pos.y += 50.0f;

			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");

			pos.x += 200.0f;
			pos.y += 150.0f;
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());

			break;
		}
		default:
			break;
		}
		/*ImGui::Begin("Settings");
		m_Level.OnImGuiRender();
		ImGui::End();*/
	}

	void GameLayer::OnEvent(MABEngine::Events::Event& e)
	{
		MABEngine::Events::EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MABEngine::Events::WindowResizeEvent>(MAB_BIND_EVENT_FN(GameLayer::OnWindowsResize));
		dispatcher.Dispatch<MABEngine::Events::MouseButtonPressedEvent>(MAB_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
		dispatcher.Dispatch<MABEngine::Events::KeyPressedEvent>(MAB_BIND_EVENT_FN(GameLayer::OnKeyboardButtonPressed));
	}

	bool GameLayer::OnWindowsResize(MABEngine::Events::WindowResizeEvent& e)
	{
		m_Width = e.GetWidth();
		m_Height = e.GetHeight();

		CreateCamera();

		return false;
	}

	bool GameLayer::OnMouseButtonPressed(MABEngine::Events::MouseButtonPressedEvent& e)
	{
		if (m_State == GameState::GameOver)
			m_Level.Reset();

		m_State = GameState::Play;
		return false;
	}

	bool GameLayer::OnKeyboardButtonPressed(MABEngine::Events::KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == MABEngine::Inputs::Mab_Key_Escape)
		{
			m_State = GameState::MainMenu;
			return true;
		}
		
		return false;
	}
	

	void GameLayer::CreateCamera()
	{
		float aspecRatio = (float)m_Width / (float)m_Height;

		float camWidth = 8.0f;
		
		float bottom = -camWidth;
		float top = camWidth;

		float left = (-camWidth) * aspecRatio;
		float right = top * aspecRatio;

		m_Camera = MABEngine::Core::CreateScope<MABEngine::Camera::OrthographicCamera>(left, right, bottom, top);
	}

}

