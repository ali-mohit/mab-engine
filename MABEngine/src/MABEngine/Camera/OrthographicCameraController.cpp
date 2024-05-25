#include "mabengine_pch.h"

#include "MABEngine/Core/Base.h"
#include "MABEngine/Logging/Log.h"
#include "MABEngine/Inputs/Input.h"
#include "MABEngine/Inputs/KeyboardCodes.h"
#include "MABEngine/Camera/OrthographicCameraController.h"

namespace MABEngine {

	namespace Camera {
		OrthographicCameraController::OrthographicCameraController(float aspectRatio, float zoomLevel)
			:m_AspectRatio(aspectRatio), 
			 m_ZoomLevel(zoomLevel),
			 m_ViewWidth(DEFAULT_VIEWPORT_SIZE),
			 m_ViewHeight((int)(DEFAULT_VIEWPORT_SIZE * aspectRatio)),
			 m_Camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel)
		{
		}

		OrthographicCameraController::OrthographicCameraController(float zoomLevel, uint32_t viewportWidth, uint32_t viewportHeight)
			:m_AspectRatio(viewportHeight != 0 ? (float)viewportWidth /(float)viewportHeight : 1.0f),
			 m_ZoomLevel(zoomLevel),
			 m_ViewWidth(viewportHeight != 0 ? viewportWidth : DEFAULT_VIEWPORT_SIZE),
			 m_ViewHeight(viewportHeight != 0 ? viewportHeight : DEFAULT_VIEWPORT_SIZE),
			 m_Camera(-m_AspectRatio * zoomLevel, m_AspectRatio * zoomLevel, -zoomLevel, zoomLevel)
		{
			MAB_CORE_ASSERT(
				viewportHeight != 0, 
				"Height of viewport size in OrthographicCameraController is 0px, so, automatically change to DEFAULT"
			);
		}

		OrthographicCameraController::~OrthographicCameraController()
		{
		}

		void OrthographicCameraController::OnUpdate(Core::EngineTimeStep ts)
		{
			if (Inputs::Input::IsKeyPressed(Inputs::Mab_Key_A)) {
				//m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
				m_CameraPosition.x -= cos(glm::radians(m_CameraZRotationSpeed)) * m_CameraTranslationSpeed * ts;
				m_CameraPosition.y -= sin(glm::radians(m_CameraZRotationSpeed)) * m_CameraTranslationSpeed * ts;
			}
			else if (Inputs::Input::IsKeyPressed(Inputs::Mab_Key_D))
			{
				//m_CameraPosition.x += m_CameraTranslationSpeed * ts;
				m_CameraPosition.x += cos(glm::radians(m_CameraZRotationSpeed)) * m_CameraTranslationSpeed * ts;
				m_CameraPosition.y += sin(glm::radians(m_CameraZRotationSpeed)) * m_CameraTranslationSpeed * ts;
			}

			if (Inputs::Input::IsKeyPressed(Inputs::Mab_Key_W)) {
				//m_CameraPosition.y += m_CameraTranslationSpeed * ts;
				m_CameraPosition.x += -sin(glm::radians(m_CameraZRotationSpeed)) * m_CameraTranslationSpeed * ts;
				m_CameraPosition.y += cos(glm::radians(m_CameraZRotationSpeed)) * m_CameraTranslationSpeed * ts;
			}
			else if (Inputs::Input::IsKeyPressed(Inputs::Mab_Key_S)) {
				//m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
				m_CameraPosition.x -= -sin(glm::radians(m_CameraZRotationSpeed)) * m_CameraTranslationSpeed * ts;
				m_CameraPosition.y -= cos(glm::radians(m_CameraZRotationSpeed)) * m_CameraTranslationSpeed * ts;
			}

			if (m_ZRotationEnabled) {
				if (Inputs::Input::IsKeyPressed(Inputs::Mab_Key_Q))
					m_CameraZRotation += m_CameraZRotationSpeed * ts;
				else if (Inputs::Input::IsKeyPressed(Inputs::Mab_Key_E))
					m_CameraZRotation -= m_CameraZRotationSpeed * ts;

				if (m_CameraZRotation > 180.0f)
					m_CameraZRotation -= 360.0f;
				else if (m_CameraZRotation <= -180.0f)
					m_CameraZRotation += 360.0f;

				m_Camera.SetRotationZ(m_CameraZRotation);
			}
			
			if (MABEngine::Inputs::Input::IsKeyPressed(Inputs::Mab_Key_F))
			{
				m_CameraZRotation = 0;
				m_ZoomLevel = 1.0f;
				m_CameraPosition = { 0.0f, 0.0f, 0.0f };

				m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
			}

			m_Camera.SetPosition(m_CameraPosition);

			m_CameraTranslationSpeed = m_ZoomLevel;
		}

		void OrthographicCameraController::OnEvent(Events::Event& e)
		{
			Events::EventDispatcher dispatcher(e);
			dispatcher.Dispatch<Events::MouseScrolledEvent>(MAB_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
			dispatcher.Dispatch<Events::WindowResizeEvent>(MAB_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

		}

		bool OrthographicCameraController::OnMouseScrolled(Events::MouseScrolledEvent& e)
		{
			m_ZoomLevel -= e.GetYOffSet() * 0.25f;
			m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);

			m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

			return false;
		}

		bool OrthographicCameraController::OnWindowResized(Events::WindowResizeEvent& e)
		{
			m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
			m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
			return false;
		}
	}
}