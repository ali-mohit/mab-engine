#include <mabengine_pch.h>
#include <MABEngine.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "SandBox2DLayer.h"


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

		MABEngine::Renderer::EngineRenderer2d::DrawQuad({ -1.0f , 0.0f }, { 2.0f, 1.0f }, { m_SolidColor1, 1.0f });
		MABEngine::Renderer::EngineRenderer2d::DrawQuad({ 0.75f , 0.0f }, { 1.0f, 2.0f }, { m_SolidColor2, 1.0f });

		MABEngine::Renderer::EngineRenderer2d::DrawQuad(
			m_rotationBoxPos,
			{ 0.5f, 0.5f },
			glm::radians(rotation),
			m_CheckerBoardTexture,
			{ m_SolidColor3, 1.0f }
		);
		MABEngine::Renderer::EngineRenderer2d::DrawQuad(
			{ 0.0f , 0.0f, 0.05f },
			{ 10.0f, 10.0f },
			m_CheckerBoardTexture,
			{10.0f, 10.0f}
		);

		MABEngine::Renderer::EngineRenderer2d::EndScene();

		//Draw Quads
		MABEngine::Renderer::EngineRenderer2d::BeginScene(m_CameraController.GetCamera());
		for (float y=-4.5f; y < 5.0; y += 0.5f) {
			for (float x=-4.5f; x < 5.0; x += 0.5f) {
				glm::vec4 color = { 0.6f, (x + 5.0f) / 10.0f, (y + 5.0f) / 10.0f, 0.8f };
				MABEngine::Renderer::EngineRenderer2d::DrawQuad({ x , y, 0.1f }, { 0.45f, 0.45f }, color);
			}
		}
		MABEngine::Renderer::EngineRenderer2d::EndScene();
	}
}

void SandBox2DLayer::OnAttach()
{
	MAB_PROFILE_FUNCTION();

	m_CheckerBoardTexture = MABEngine::Textures::Texture2D::Create("assets/textures/Checkerboard.png");
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
