#include "mabengine_pch.h"
#include <MABEngine.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "DockSpaceView.h"

namespace SandBoxLayers
{
	DockSpaceView::DockSpaceView(uint32_t width, uint32_t height)
		:Layer("SandBox ViewPort"),
		m_Width(width),
		m_Height(height),
		m_CameraController(height != 0 ? (float)width / (float)height : 1.0f, 1.0f)
	{
		m_CameraController.SetZRotationEnabled(true);
		m_CameraController.SetZoomLevel(1.5f);
	}

	DockSpaceView::~DockSpaceView()
	{

	}

	void DockSpaceView::OnImGuiRender()
	{
		MAB_PROFILE_FUNCTION();

		MakeSettingWindow();
	}

	void DockSpaceView::OnAttach()
	{
		MAB_PROFILE_FUNCTION();

		m_CheckerBoardTexture = MABEngine::Textures::Texture2D::Create("assets/textures/Checkerboard.png");
		m_SpriteSheet = MABEngine::Textures::Texture2D::Create("assets/textures/Cartography_Sheet_2x.png");
		m_Castle = MABEngine::Textures::SubTexture2D::CreateFromCoordinates(m_SpriteSheet, { 0.0, 9.0 }, { 128.0f , 128.0f }, { 2, 1 });

	}

	void DockSpaceView::OnEvent(MABEngine::Events::Event& event)
	{
		m_CameraController.OnEvent(event);
	}

	void DockSpaceView::MakeSettingWindow()
	{
		ImGui::Begin("Settings");

		auto statics = MABEngine::Renderer::EngineRenderer2d::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", statics.NumberOfDrawCalls);
		ImGui::Text("Quads: %d", statics.QuadCounts);
		ImGui::Text("Vertices: %d", statics.GetTotalVertexCount());
		ImGui::Text("Edeges: %d", statics.GetTotalEdgetCount());

		ImGui::ColorEdit3("Square Color1", glm::value_ptr(m_SolidColor1));
		ImGui::DragFloat("Rotation Box Value", &m_rotationBox);

		ImGui::End();
	}

	void DockSpaceView::OnUpdate(MABEngine::Core::EngineTimeStep ts)
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
			MAB_PROFILE_SCOPE("Rendering");
			MABEngine::Renderer::EngineRenderer2d::BeginScene(m_CameraController.GetCamera());

			//Background
			MABEngine::Renderer::EngineRenderer2d::DrawQuad(
				{ 0.0f , 0.0f, -0.2f },
				{ 10.0f, 10.0f },
				m_CheckerBoardTexture,
				{ 10.0f, 10.0f }
			);

			//Box 01
			MABEngine::Renderer::EngineRenderer2d::DrawQuad(
				{ -1.0f , 0.0f },
				{ 2.0f, 1.0f },
				glm::radians(m_rotationBox),
				{ m_SolidColor1, 1.0f }
			);

			//Castle Texture
			MABEngine::Renderer::EngineRenderer2d::DrawQuad(
				{ 1.0f, 0.0f, 0.3f },
				{ 2.0f, 1.0f },
				glm::radians(0.0f),
				m_Castle,
				{ 0.0f, 0.0f, 0.0f , 1.0f }
			);

			MABEngine::Renderer::EngineRenderer2d::EndScene();

		}
	}
}