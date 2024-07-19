#include <mabengine_pch.h>
#include <MABEngine.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "SandBox2DLayer.h"

namespace SandBoxLayers
{
	SandBox2DLayer::SandBox2DLayer(uint32_t width, uint32_t height)
		:Layer("2D Layer Test"),
		m_Width(width),
		m_Height(height),
		m_CameraController(height != 0 ? (float)width / (float)height : 1.0f, 1.0f)
	{
		m_CameraController.SetZRotationEnabled(true);
		m_CameraController.SetZoomLevel(1.5f);
	}

	void SandBox2DLayer::OnUpdate(MABEngine::Core::EngineTimeStep ts)
	{
		MAB_PROFILE_FUNCTION();

		m_CameraController.OnUpdate(ts);

		MABEngine::Renderer::EngineRenderer2d::ResetStats();
		// Rendering Pre
		{
			MAB_PROFILE_SCOPE("PreProcessRendering");
			MABEngine::Renderer::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
			MABEngine::Renderer::RenderCommand::Clear();
		}

		// Rendering 
		{
			static float rotation = 0.0;
			rotation += ts * 50.0f;

			MAB_PROFILE_SCOPE("Rendering");
			MABEngine::Renderer::EngineRenderer2d::BeginScene(m_CameraController.GetCamera());

			/*MABEngine::Renderer::EngineRenderer2d::DrawQuad({ -1.0f , 0.0f }, { 2.0f, 1.0f }, { m_SolidColor1, 1.0f });
			MABEngine::Renderer::EngineRenderer2d::DrawQuad({ 0.75f , 0.0f }, { 1.0f, 2.0f }, { m_SolidColor2, 1.0f });

			MABEngine::Renderer::EngineRenderer2d::DrawQuad(
				m_rotationBoxPos,
				{ 0.5f, 0.5f },
				glm::radians(rotation),
				m_CheckerBoardTexture,
				{ m_SolidColor3, 1.0f }
			);*/

			MABEngine::Renderer::EngineRenderer2d::DrawQuad(
				{ 0.0f , 0.0f, -0.2f },
				{ 10.0f, 10.0f },
				m_CheckerBoardTexture,
				{ 10.0f, 10.0f }
			);

			MABEngine::Renderer::EngineRenderer2d::DrawQuad(
				{ 0.0, 0.0, 0.01f },
				{ 10.0f, 10.0f },
				m_PaperBackground,
				{ 1.0f, 1.0f }
			);

			MABEngine::Renderer::EngineRenderer2d::DrawQuad(
				{ 0.0f, 0.0f, 0.3f },
				{ 2.0f, 1.0f },
				glm::radians(0.0f),
				m_Castle,
				{ 0.0f, 0.0f, 0.0f , 1.0f }
			);

			MABEngine::Renderer::EngineRenderer2d::EndScene();

		}

		if (MABEngine::Inputs::Input::IsMouseButtonPressed(MABEngine::Inputs::Mab_Mouse_Button_1)) {
			auto [x, y] = MABEngine::Inputs::Input::GetMousePos();
			auto width = MABEngine::Core::Application::Get().GetWindow().GetWidth();
			auto height = MABEngine::Core::Application::Get().GetWindow().GetHeight();

			auto bounds = m_CameraController.GetBounds();
			auto pos = m_CameraController.GetCamera().GetPosition();

			x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
			y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
			m_ParticleProperties.Position = { x + pos.x, y + pos.y };
			for (int i = 0; i < 5; i++) {
				m_ParticleSystem.Emit(m_ParticleProperties);
			}
		}
		m_ParticleSystem.OnUpdate(ts);
		m_ParticleSystem.OnRender(m_CameraController.GetCamera());
	}

	void SandBox2DLayer::OnAttach()
	{
		MAB_PROFILE_FUNCTION();

		m_CheckerBoardTexture = MABEngine::Textures::Texture2D::Create("assets/textures/Checkerboard.png");
		m_PaperBackground = MABEngine::Textures::Texture2D::Create("assets/textures/parchmentBasic.png");
		m_SpriteSheet = MABEngine::Textures::Texture2D::Create("assets/textures/Cartography_Sheet_2x.png");
		m_Castle = MABEngine::Textures::SubTexture2D::CreateFromCoordinates(m_SpriteSheet, { 0.0, 9.0 }, { 128.0f , 128.0f }, { 2, 1 });

		m_ParticleProperties.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
		m_ParticleProperties.ColorEnd = { 200 / 255.0f, 58 / 255.0f, 41 / 255.0f, 1.0f };
		m_ParticleProperties.Position = { 0.0f, 0.0f };
		m_ParticleProperties.Velocity = { 0.0f, 0.0f };
		m_ParticleProperties.VelocityVariation = { 3.0f, 1.0f };
		m_ParticleProperties.SizeBegin = 0.3f;
		m_ParticleProperties.SizeEnd = 0.0f;
		m_ParticleProperties.SizeVariation = 0.3f;
		m_ParticleProperties.LifeTime = 5.0f;
	}

	void SandBox2DLayer::OnImGuiRender()
	{
		MAB_PROFILE_FUNCTION();

		ImGui::Begin("Settings");

		auto statics = MABEngine::Renderer::EngineRenderer2d::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", statics.NumberOfDrawCalls);
		ImGui::Text("Quads: %d", statics.QuadCounts);
		ImGui::Text("Vertices: %d", statics.GetTotalVertexCount());
		ImGui::Text("Edeges: %d", statics.GetTotalEdgetCount());

		ImGui::ColorEdit3("Square Color1", glm::value_ptr(m_SolidColor1));
		ImGui::ColorEdit3("Square Color2", glm::value_ptr(m_SolidColor2));
		ImGui::ColorEdit3("Square Color3", glm::value_ptr(m_SolidColor3));
		ImGui::DragFloat3("Rotation Box Pos", glm::value_ptr(m_rotationBoxPos));

		ImGui::End();
	}

	void SandBox2DLayer::OnEvent(MABEngine::Events::Event& event)
	{
		m_CameraController.OnEvent(event);
	}
}