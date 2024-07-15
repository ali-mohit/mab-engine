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

	// Rendering Pre
	{
		MAB_PROFILE_SCOPE("PreProcessRendering");
		MABEngine::Renderer::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		MABEngine::Renderer::RenderCommand::Clear();
	}

	// Rendering 
	{
		MAB_PROFILE_SCOPE("Rendering");
		MABEngine::Renderer::EngineRenderer2d::BeginScene(m_CameraController.GetCamera());

		MABEngine::Renderer::EngineRenderer2d::DrawQuad({ -1.0f , 0.0f }, { 2.0f, 1.0f }, { m_SolidColor1, 1.0f });
		MABEngine::Renderer::EngineRenderer2d::DrawQuad({ 0.75f , 0.0f }, { 1.0f, 2.0f }, { m_SolidColor2, 1.0f });

		MABEngine::Renderer::EngineRenderer2d::DrawQuad({ -1.0f , -1.0f }, { 0.5f, 0.5f }, 45.0f, { m_SolidColor3, 1.0f });
		MABEngine::Renderer::EngineRenderer2d::DrawQuad({ 0.0f , 0.0f, 0.1f }, { 10.0f, 10.0f }, m_CheckerBoardTexture);

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
	ImGui::ColorEdit3("Square Color1", glm::value_ptr(m_SolidColor1));
	ImGui::ColorEdit3("Square Color2", glm::value_ptr(m_SolidColor2));
	ImGui::ColorEdit3("Square Color3", glm::value_ptr(m_SolidColor3));
	ImGui::End();
}

void SandBox2DLayer::OnEvent(MABEngine::Events::Event& event)
{
	m_CameraController.OnEvent(event);
}
