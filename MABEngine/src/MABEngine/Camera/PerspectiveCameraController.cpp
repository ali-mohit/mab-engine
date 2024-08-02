#include "mabengine_pch.h"
#include "MABEngine/Camera/PerspectiveCameraController.h"

#include "MABEngine/Core/Base.h"
#include "MABEngine/Events/Event.h"
#include "MABEngine/Inputs/Input.h"


namespace MABEngine {

	namespace Camera {
		PerspectiveCameraController::PerspectiveCameraController()
		{
		}
		PerspectiveCameraController::PerspectiveCameraController(
			float nearClip, float farClip, float verticalFOV,
			uint32_t width, uint32_t height
		):
			m_Camera(nearClip, farClip, verticalFOV, width, height)
		{
		}

		PerspectiveCameraController::PerspectiveCameraController(
			float nearClip, float farClip, float verticalFOV,
			uint32_t width, uint32_t height,
			const glm::vec3& cameraPos, const glm::vec3& cameraTarget
		):
			m_Camera(nearClip, farClip, verticalFOV, width, height,cameraPos, cameraTarget)
		{
		}

		PerspectiveCameraController::PerspectiveCameraController(
			float nearClip, float farClip, float verticalFOV,
			uint32_t width, uint32_t height,
			const glm::vec3& cameraPos, const glm::vec3& cameraTarget, const glm::vec3& upDirection
		):
			m_Camera(nearClip, farClip, verticalFOV, width, height, cameraPos, cameraTarget, upDirection)
		{
		}

		void PerspectiveCameraController::OnUpdate(Core::EngineTimeStep ts)
		{
			MAB_PROFILE_FUNCTION();

			if (m_HandleKeyboardEventsFlag) {
				auto isCtrlPressed = Inputs::Input::IsKeyPressed(Inputs::Mab_Key_Left_Control) ||
					Inputs::Input::IsKeyPressed(Inputs::Mab_Key_Left_Control);
				auto isLeftClickPressed = Inputs::Input::IsMouseButtonPressed(Inputs::Mab_Mouse_Button_Left);
				auto isRightClickPressed = Inputs::Input::IsMouseButtonPressed(Inputs::Mab_Mouse_Button_Right);

				if (isCtrlPressed && isLeftClickPressed) {
					auto [x, y] = Inputs::Input::GetMousePos();
					

					if (m_IsLastMousePosSet) {
						auto delta = glm::vec2(x, y) - m_LastMousePosition;
						auto absX = std::abs(delta.x);
						auto absY = std::abs(delta.y);
						float deltaC = 10;

						float angleX = 0;
						float angleY = 0;
						float rotationValue = glm::radians(m_CameraRotationSpeed);
						
						if (absX >= absY)
						{
							delta.x = (absX - deltaC) <= 0 ? 0.0f : delta.x / absX;
							delta.y = 0;
						}
						else {
							delta.x = 0;
							delta.y = (absY - deltaC) <= 0 ? 0.0f : delta.y / absY;
						}

						angleX = rotationValue * ts * delta.x;
						angleY = rotationValue * ts * delta.y;

						m_Camera.RotateAroundTargetLocal(angleX, -angleY);
					}
					
					m_IsLastMousePosSet = true;
					m_LastMousePosition = { x, y };
				}
				else {
					m_IsLastMousePosSet = false;

				}

				if (MABEngine::Inputs::Input::IsKeyPressed(Inputs::Mab_Key_F))
				{
					//Reset Scene
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

			m_Camera.OnResize(width, height);
		}

		bool PerspectiveCameraController::OnMouseScrolled(Events::MouseScrolledEvent& e)
		{
			MAB_PROFILE_FUNCTION();

			float translationDelta = e.GetYOffSet() * 0.1f * m_CameraTranslationSpeed;

			m_Camera.MoveTowardTarget(translationDelta);
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