#include "mabengine_pch.h"
#include <MABEngine.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "MainLayer.h"

namespace LightsAndShadows {
	namespace Layers
	{
		MainLayer::MainLayer(uint32_t width, uint32_t height)
			:Layer("MAB Light And Shadows"),
			m_Width(width),
			m_Height(height),
			m_OrthoCameraController(height != 0 ? (float)width / (float)height : 1.0f, 1.0f)
		{
			m_OrthoCameraController.SetZRotationEnabled(true);
			m_OrthoCameraController.SetZoomLevel(1.5f);
			m_OrthoCameraController.SetHandleWindowResizeEnbaled(false);

			m_Scene = MABEngine::Core::CreateRef<MABEngine::Scene::SceneManagement>("Main");
			
			m_PersCameraController = MABEngine::Camera::PerspectiveCameraController(
				MABEngine::Camera::CameraSpecification::CreateTargetCamera(
					45.0f, 0.01, 100.0f,
					width, height,
					{ 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, MABEngine::Camera::PerspectiveCamera::WORLD_UP
				)
			);

		}

		MainLayer::~MainLayer()
		{

		}

		void MainLayer::OnImGuiRender()
		{
			MAB_PROFILE_FUNCTION();

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

		void MainLayer::OnAttach()
		{
			MAB_PROFILE_FUNCTION();

			m_CheckerBoardTexture = MABEngine::Textures::Texture2D::Create("assets/textures/Checkerboard.png");
			m_SpriteSheet = MABEngine::Textures::Texture2D::Create("assets/textures/Cartography_Sheet_2x.png");
			m_Castle = MABEngine::Textures::SubTexture2D::CreateFromCoordinates(m_SpriteSheet, { 0.0, 9.0 }, { 128.0f , 128.0f }, { 2, 1 });

			MABEngine::Renderer::FrameBufferSpecification fbSpec(m_Width, m_Height);
			m_FramBuffer = MABEngine::Renderer::FrameBuffer::Create(fbSpec);

			{
				m_Square01 = m_Scene->CreateEntity("square01");
				m_Square01.AddComponent<MABEngine::Components::SpriteRendererComponent>(glm::vec4({ 0.0f, 0.0f, 0.0f, 1.0f }), nullptr, m_Castle);

				auto& square01Translate = m_Square01.GetComponent<MABEngine::Components::TransformComponent>();
				square01Translate.Translation = { 1.0f, 0.0f, 0.0f };
				square01Translate.Scale = { 2.0f, 1.0f , 1.0f };
			}

			{
				m_Square02 = m_Scene->CreateEntity("square02");
				m_Square02.AddComponent<MABEngine::Components::SpriteRendererComponent>(glm::vec4({ m_SolidColor1, 1.0f }));

				auto& square02Translate = m_Square02.GetComponent<MABEngine::Components::TransformComponent>();
				square02Translate.Translation = { -1.0f , 0.0f, 0.0 };
				square02Translate.Scale = { 2.0f, 1.0f, 1.0f };
				square02Translate.Rotation = { 0.0f, 0.0f, glm::radians(m_rotationBox) };

			}
		}

		void MainLayer::OnEvent(MABEngine::Events::Event& event)
		{
			//m_OrthoCameraController.OnEvent(event);
			m_PersCameraController.OnEvent(event);
		}

		void MainLayer::MakeSettingWindow()
		{
			if (m_ShowSettingBox) {
				ImGui::Begin("Settings");

				auto statics = MABEngine::Renderer::EngineRenderer2d::GetStats();
				ImGui::Text("Renderer2D Stats:");
				ImGui::Text("Draw Calls: %d", statics.NumberOfDrawCalls);
				ImGui::Text("Quads: %d", statics.QuadCounts);
				ImGui::Text("Vertices: %d", statics.GetTotalVertexCount());
				ImGui::Text("Edeges: %d", statics.GetTotalEdgetCount());

				if (ImGui::ColorEdit3("Square Color1", glm::value_ptr(m_SolidColor1)))
				{
					auto& sprite = m_Square02.GetComponent<MABEngine::Components::SpriteRendererComponent>();
					sprite.Color = glm::vec4({ m_SolidColor1, 1.0f });
				}

				if (ImGui::DragFloat("Rotation Box Value", &m_rotationBox))
				{
					auto& square02Translate = m_Square02.GetComponent<MABEngine::Components::TransformComponent>();
					square02Translate.Rotation = { 0.0f, 0.0f, glm::radians(m_rotationBox) };
				}

				ImGui::End();
			}
		}

		void MainLayer::MakeViewWindow()
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0.0f, 0.0f});
			ImGui::Begin("View");
			
			m_IsViewFocused = ImGui::IsWindowFocused();
			m_IsMouseHover = ImGui::IsWindowHovered();

			m_OrthoCameraController.SetHandleKeyboardEventsFlag(m_IsViewFocused);
			m_PersCameraController.SetHandleKeyboardEventsFlag(m_IsViewFocused);

			MABEngine::Core::Application::Get().GetImGuiLayer()->SetBlockMouseEvents(!m_IsMouseHover);
			MABEngine::Core::Application::Get().GetImGuiLayer()->SetBlockKeyboardEvents(!m_IsViewFocused);
			

			ImVec2 currentSize = ImGui::GetContentRegionAvail();
			if (((int)currentSize.x != m_ViewportWidth || (int)currentSize.y != m_ViewportHeight) &&
				(int)currentSize.x > 0 &&
				(int)currentSize.y > 0) {
				m_ViewportWidth = currentSize.x;
				m_ViewportHeight = currentSize.y;
				
				m_FramBuffer->Resize((uint32_t)m_ViewportWidth, (uint32_t)m_ViewportHeight);

				m_OrthoCameraController.Resize(m_ViewportWidth, m_ViewportHeight);

				m_PersCameraController.Resize(m_ViewportWidth, m_ViewportHeight);
			}

			uint32_t textureId = m_FramBuffer->GetColorAttachmentID();
			ImGui::Image(
				(void*)textureId,
				ImVec2{ (float)m_ViewportWidth, (float)m_ViewportHeight },
				ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f }
			);

			ImGui::End();
			ImGui::PopStyleVar();
		}

		void MainLayer::OnUpdate(MABEngine::Core::EngineTimeStep ts)
		{
			MAB_PROFILE_FUNCTION();

			//m_OrthoCameraController.OnUpdate(ts);
			m_PersCameraController.OnUpdate(ts);

			MABEngine::Renderer::EngineRenderer2d::ResetStats();
			// Rendering Pre
			{
				MAB_PROFILE_SCOPE("PreProcessRendering");

				if (m_IsDockSapceActive)
					m_FramBuffer->Bind();

				MABEngine::Renderer::RenderCommand::SetClearColor({ 0.4f, 0.4f, 0.4f, 1 });
				MABEngine::Renderer::RenderCommand::Clear();
			}

			// Rendering 
			{
				MAB_PROFILE_SCOPE("Rendering");
				//MABEngine::Renderer::EngineRenderer2d::BeginScene(m_OrthoCameraController.GetCamera());
				MABEngine::Renderer::EngineRenderer2d::BeginScene(m_PersCameraController.GetCamera());

				
				//Background
				MABEngine::Renderer::EngineRenderer2d::DrawQuad(
					{ 0.0f , 0.0f, -0.2f },
					{ 10.0f, 10.0f },
					m_CheckerBoardTexture,
					{ 10.0f, 10.0f }
				);

				//Box
				auto squre02Sprite = m_Square02.GetComponent<MABEngine::Components::SpriteRendererComponent>();
				auto squre02Translate = m_Square02.GetComponent<MABEngine::Components::TransformComponent>();

				MABEngine::Renderer::EngineRenderer2d::DrawQuad(
					squre02Translate.Translation,
					squre02Translate.Scale,
					squre02Translate.Rotation.z,
					squre02Sprite.Color
				);

				auto squre01Sprite = m_Square01.GetComponent<MABEngine::Components::SpriteRendererComponent>();
				auto squre01Translate = m_Square01.GetComponent<MABEngine::Components::TransformComponent>();

				//Castle Texture
				MABEngine::Renderer::EngineRenderer2d::DrawQuad(
					squre01Translate.Translation,
					squre01Translate.Scale,
					glm::radians(0.0f),
					squre01Sprite.SubTexture,
					squre01Sprite.Color
				);

				MABEngine::Renderer::EngineRenderer2d::EndScene();

				if (m_IsDockSapceActive)
					m_FramBuffer->UnBind();
			}
		}
	}
}