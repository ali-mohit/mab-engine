#include "mabengine_pch.h"
#include "MABEngine/Camera/PerspectiveCameraController.h"

#include "MABEngine/Core/Base.h"
#include "MABEngine/Core/Application.h"
#include "MABEngine/Camera/CameraSpecification.h"
#include "MABEngine/Events/Event.h"
#include "MABEngine/Inputs/Input.h"


namespace MABEngine {

	namespace Camera {
		PerspectiveCameraController::PerspectiveCameraController()
			:m_Camera()
		{
		}

		PerspectiveCameraController::PerspectiveCameraController(const CameraSpecification& spec)
			:m_Camera(spec)
		{
		}

		PerspectiveCameraController::PerspectiveCameraController(
			float nearClip, float farClip, float verticalFOV,
			uint32_t width, uint32_t height
		):
			m_Camera(CameraSpecification::CreateFreeCam(verticalFOV, nearClip, farClip, width, height)),
			m_Width(width),
			m_Height(height)
		{
		}

		PerspectiveCameraController::PerspectiveCameraController(
			float nearClip, float farClip, float verticalFOV,
			uint32_t width, uint32_t height,
			const glm::vec3& cameraPos, const glm::vec3& cameraTarget
		):
			m_Camera(CameraSpecification::CreateFreeCam(
				verticalFOV, nearClip, farClip,
				width, height,
				cameraPos, glm::normalize(cameraTarget - cameraPos), glm::vec3(0.0f, 1.0f, 0.0f)
				)
			),
			m_Width(width),
			m_Height(height)
		{
		}

		PerspectiveCameraController::PerspectiveCameraController(
			float nearClip, float farClip, float verticalFOV,
			uint32_t width, uint32_t height,
			const glm::vec3& cameraPos, const glm::vec3& cameraTarget, const glm::vec3& upDirection
		):
			m_Camera(CameraSpecification::CreateFreeCam(
				verticalFOV, nearClip, farClip,
				width, height,
				cameraPos, glm::normalize(cameraTarget - cameraPos), upDirection))
		{
		}

		void PerspectiveCameraController::OnUpdate(Core::EngineTimeStep ts)
		{
			MAB_PROFILE_FUNCTION();

			if (m_HandleKeyboardEventsFlag) {
				auto isCtrlPressed = Inputs::Input::IsKeyPressed(Inputs::Mab_Key_Left_Control) ||
					Inputs::Input::IsKeyPressed(Inputs::Mab_Key_Right_Control);

				auto isXPressed = Inputs::Input::IsKeyPressed(Inputs::Mab_Key_X);

				auto isLeftClickPressed = Inputs::Input::IsMouseButtonPressed(Inputs::Mab_Mouse_Button_Left);
				auto isRightClickPressed = Inputs::Input::IsMouseButtonPressed(Inputs::Mab_Mouse_Button_Right);
				auto isMiddleClickPressed = Inputs::Input::IsMouseButtonPressed(Inputs::Mab_Mouse_Button_Middle);

				if (isCtrlPressed) {
					
					float width = m_Width;
					float height = m_Height;

					// Prevents camera from jumping on the first click
					if (m_FirstClick)
					{
						m_FirstClick = false;
						auto[last_x, last_y] = Inputs::Input::GetMousePos();
						m_LastMousePosition = { last_x, last_y };
					}

					// Fetches the coordinates of the cursor
					auto [mouseX, mouseY] = Inputs::Input::GetMousePos();
					
					float moveX = (float)(mouseX - m_LastMousePosition.x);
					float moveY = (float)(mouseY - m_LastMousePosition.y);

					if (isLeftClickPressed && !isXPressed) {
						// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
						// and then "transforms" them into degrees 
						float rotY = m_RotationSensitivity * moveY;
						float rotX = m_RotationSensitivity * moveX;

						m_Camera.LocalXYRotation(rotX, rotY);
					}
					else if (isLeftClickPressed && isXPressed) {
						float rotX = m_RotationSensitivity * moveX;
						m_Camera.RollRotation(rotX);
					}
					else if (isMiddleClickPressed) {
						float valueX = m_TranslationSensitivity * moveX;
						float valueY = m_TranslationSensitivity * moveY;

						m_Camera.TruckAndPedestalMovement(-valueX, valueY);
					}
					else if (isRightClickPressed) {

						float valueX = m_TranslationSensitivity * moveX;
						float valueY = m_TranslationSensitivity * moveY;

						m_Camera.MoveDolly(-valueY);
					}
					
					
					m_LastMousePosition = { mouseX, mouseY };
				}
				else {
					m_FirstClick = true;
				}

				if (MABEngine::Inputs::Input::IsKeyPressed(Inputs::Mab_Key_F))
				{
					//Reset Scene
					m_Camera = PerspectiveCamera(m_Camera.GetCameraSetupSpecification());
				}
			}

		}
		
		void PerspectiveCameraController::OnEvent(Events::Event& e)
		{
			MAB_PROFILE_FUNCTION();

			Events::EventDispatcher dispatcher(e);
			dispatcher.Dispatch<Events::MouseScrolledEvent>(MAB_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));

			if (m_HandleWindowResizeEnabled)
				dispatcher.Dispatch<Events::WindowResizeEvent>(MAB_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
		}

		void PerspectiveCameraController::Resize(uint32_t width, uint32_t height)
		{
			MAB_PROFILE_FUNCTION();

			if (height == 0 || width == 0) return;

			m_Camera.Resize(width, height);
			m_Width = width;
			m_Height = height;
		}

		bool PerspectiveCameraController::OnMouseScrolled(Events::MouseScrolledEvent& e)
		{
			MAB_PROFILE_FUNCTION();

			float translationDelta = -e.GetYOffSet() * m_ZoomSensitivity;

			m_Camera.ZoomCamera(translationDelta);
			return false;
		}

		bool PerspectiveCameraController::OnWindowResized(Events::WindowResizeEvent& e)
		{
			MAB_PROFILE_FUNCTION();

			Resize(e.GetWidth(), e.GetHeight());

			return false;
		}
	}
}