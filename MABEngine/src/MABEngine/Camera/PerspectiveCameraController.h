#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Core/TimeStep.h"
#include "MABEngine/Events/Event.h"
#include "MABEngine/Events/MouseEvent.h"
#include "MABEngine/Events/ApplicationEvent.h"
#include "MABEngine/Camera/PerspectiveCamera.h"


namespace MABEngine {

	namespace Camera {
		class MABENGINE_API PerspectiveCameraController {
		public:
			PerspectiveCameraController();
			PerspectiveCameraController(const CameraSpecification& spec);
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

			PerspectiveCamera& GetCamera() { return m_Camera; }
			const PerspectiveCamera& GetCamera() const { return m_Camera; }

			bool GetHandleKeyboardEventsFlag() const { return m_HandleKeyboardEventsFlag; }
			void SetHandleKeyboardEventsFlag(bool handled) { m_HandleKeyboardEventsFlag = handled; }

		private:
			bool OnMouseScrolled(Events::MouseScrolledEvent& e);
			bool OnWindowResized(Events::WindowResizeEvent& e);
		private:
			PerspectiveCamera m_Camera;
			uint32_t m_Width = 1280;
			uint32_t m_Height = 720;

			float m_RotationSensitivity = 0.2f;
			float m_TranslationSensitivity = 0.02f;
			float m_ZoomSensitivity = 2.0f;

			bool m_HandleWindowResizeEnabled = true;
			bool m_HandleKeyboardEventsFlag = true;

			bool m_FirstClick = false;
			glm::vec2 m_LastMousePosition = { 0.0f, 0.0f };
		};
	}
}
