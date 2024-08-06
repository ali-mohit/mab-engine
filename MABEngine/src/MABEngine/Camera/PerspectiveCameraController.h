#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Core/TimeStep.h"
#include "MABEngine/Events/Event.h"
#include "MABEngine/Events/MouseEvent.h"
#include "MABEngine/Events/ApplicationEvent.h"
#include "MABEngine/Camera/PerspectiveFreeCamera.h"
#include "MABEngine/Camera/PerspectiveTargetCamera.h"


namespace MABEngine {

	namespace Camera {
		class MABENGINE_API PerspectiveCameraController {
		public:
			PerspectiveCameraController();
			PerspectiveCameraController(float nearClip, float farClip, float verticalFOV, uint32_t width, uint32_t height);

			PerspectiveCameraController(
				float nearClip, float farClip, float verticalFOV,
				uint32_t width, uint32_t height,
				const glm::vec3& cameraPos, const glm::vec3& cameraTarget
			);

			PerspectiveCameraController(
				float nearClip, float farClip, float verticalFOV,
				uint32_t width, uint32_t height,
				const glm::vec3& cameraPos, const glm::vec3& cameraTarget, const glm::vec3& upDirection
			);

			~PerspectiveCameraController() = default;

			void OnUpdate(Core::EngineTimeStep ts);
			void OnEvent(Events::Event& e);

			void Resize(uint32_t width, uint32_t height);

			PerspectiveTargetCamera& GetCamera() { return m_Camera; }
			const PerspectiveTargetCamera& GetCamera() const { return m_Camera; }

			bool GetHandleKeyboardEventsFlag() const { return m_HandleKeyboardEventsFlag; }
			void SetHandleKeyboardEventsFlag(bool handled) { m_HandleKeyboardEventsFlag = handled; }
		private:
			bool OnMouseScrolled(Events::MouseScrolledEvent& e);
			bool OnWindowResized(Events::WindowResizeEvent& e);
		private:
			PerspectiveTargetCamera m_Camera;
			
			float m_CameraTranslationSpeed = 10.0f;
			float m_CameraRotationSpeed = 5.0f;

			bool m_HandleWindowResizeEnabled = false;
			bool m_HandleKeyboardEventsFlag = true;

			bool m_IsLastMousePosSet = false;
			glm::vec2 m_LastMousePosition = { 0.0f, 0.0f };
		};
	}
}
