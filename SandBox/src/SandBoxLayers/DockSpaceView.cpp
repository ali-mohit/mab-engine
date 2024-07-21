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

		if (m_IsDockSapceActive) {

            static bool opt_fullscreen = true;
            static bool opt_padding = false;
            static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

            // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
            // because it would be confusing to have two docking targets within each others.
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            if (opt_fullscreen)
            {
                const ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->WorkPos);
                ImGui::SetNextWindowSize(viewport->WorkSize);
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            }
            else
            {
                dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
            }

            // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
            // and handle the pass-thru hole, so we ask Begin() to not render a background.
            if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                window_flags |= ImGuiWindowFlags_NoBackground;

            // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
            // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
            // all active windows docked into it will lose their parent and become undocked.
            // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
            // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
            if (!opt_padding)
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("Dockspace view", &m_IsDockSapceActive, window_flags);
            if (!opt_padding)
                ImGui::PopStyleVar();

            if (opt_fullscreen)
                ImGui::PopStyleVar(2);

            // Submit the DockSpace
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    // Disabling fullscreen would allow the window to be moved to the front of other windows,
                    // which we can't undo at the moment without finer window depth/z control.
                    ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                    ImGui::MenuItem("Padding", NULL, &opt_padding);
                    ImGui::Separator();
					if (ImGui::MenuItem("Show Setting Window", "", m_ShowSettingBox)) {
						m_ShowSettingBox = !m_ShowSettingBox;
					}
					ImGui::Separator();

					if (ImGui::MenuItem("Close Application", NULL))
						MABEngine::Core::Application::Get().CloseApplication();

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

			MakeSettingWindow();

			MakeViewWindow();

            ImGui::End();
		}
		else {
            MakeSettingWindow();
		}
		
	}

	void DockSpaceView::OnAttach()
	{
		MAB_PROFILE_FUNCTION();

		m_CheckerBoardTexture = MABEngine::Textures::Texture2D::Create("assets/textures/Checkerboard.png");
		m_SpriteSheet = MABEngine::Textures::Texture2D::Create("assets/textures/Cartography_Sheet_2x.png");
		m_Castle = MABEngine::Textures::SubTexture2D::CreateFromCoordinates(m_SpriteSheet, { 0.0, 9.0 }, { 128.0f , 128.0f }, { 2, 1 });

		MABEngine::Renderer::FrameBufferSpecification fbSpec(m_Width, m_Height);
		m_FramBuffer = MABEngine::Renderer::FrameBuffer::Create(fbSpec);
	}

	void DockSpaceView::OnEvent(MABEngine::Events::Event& event)
	{
		m_CameraController.OnEvent(event);
	}

	void DockSpaceView::MakeSettingWindow()
	{
		if (m_ShowSettingBox) {
			ImGui::Begin("Settings");

			auto statics = MABEngine::Renderer::EngineRenderer2d::GetStats();
			ImGui::Text("Renderer2D Stats:");
			ImGui::Text("Draw Calls: %d", statics.NumberOfDrawCalls);
			ImGui::Text("Quads: %d", statics.QuadCounts);
			ImGui::Text("Vertices: %d", statics.GetTotalVertexCount());
			ImGui::Text("Edeges: %d", statics.GetTotalEdgetCount());

			ImGui::ColorEdit3("Square Color1", glm::value_ptr(m_SolidColor1));
			ImGui::DragFloat("Rotation Box Value", &m_rotationBox);
			ImGui::Checkbox("Dockspace Viewport", &m_IsDockSapceActive);

			ImGui::End();
		}
	}

	void DockSpaceView::MakeViewWindow()
	{
		ImGui::Begin("View");

		uint32_t textureId = m_FramBuffer->GetColorAttachmentID();
		ImGui::Image((void*)textureId, ImVec2{m_Width/2.0f, m_Height/2.0f}, ImVec2{0.0f, 1.0f}, ImVec2{1.0f, 0.0f});

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

			if (m_IsDockSapceActive)
				m_FramBuffer->Bind();

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

			if (m_IsDockSapceActive)
				m_FramBuffer->UnBind();
		}
	}
}