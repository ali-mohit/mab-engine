#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Core/TimeStep.h"
#include "MABEngine/Camera/OrthographicCameraBounds.h"
#include "MABEngine/Camera/OrthographicCamera.h"
#include "MABEngine/Events/Event.h"
#include "MABEngine/Events/ApplicationEvent.h"
#include "MABEngine/Events/MouseEvent.h"

namespace MABEngine {

	namespace Camera {

		const uint32_t DEFAULT_VIEWPORT_SIZE = 1080;

		class MABENGINE_API OrthographicCameraController {
		public:
			OrthographicCameraController(float aspectRatio, float zoomLevel);
			OrthographicCameraController(float zoomLevel, uint32_t width, uint32_t height);

			~OrthographicCameraController();

			void OnUpdate(Core::EngineTimeStep ts);
			void OnEvent(Events::Event& e);

			void Resize(uint32_t width, uint32_t height);

			bool GetZRotationEnabled() const { return m_ZRotationEnabled; }
			void SetZRotationEnabled(bool enable) { m_ZRotationEnabled = enable; }

			bool GetHandleWindowResizeEnbaled() const { return m_HandleWindowResizeEnabled; }
			void SetHandleWindowResizeEnbaled(bool enabled) { m_HandleWindowResizeEnabled = enabled; }

			OrthographicCamera& GetCamera() { return m_Camera; }
			const OrthographicCamera& GetCamera() const { return m_Camera; }

			const glm::vec3& GetCameraPosition() const { return m_CameraPosition; }
			void SetCameraPosition(const glm::vec3& position) { m_CameraPosition = { position.x, position.y, position.z }; }

			const float GetZoomLevel();
			void SetZoomLevel(float zoomLevel);

			const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

			bool GetHandleKeyboardEventsFlag() const { return m_HandleKeyboardEventsFlag; }
			void SetHandleKeyboardEventsFlag(bool handled) { m_HandleKeyboardEventsFlag = handled; }

		private:
			bool OnMouseScrolled(Events::MouseScrolledEvent& e);
			bool OnWindowResized(Events::WindowResizeEvent& e);
		private:
			float m_ZoomLevel = 1.0f;
			float m_AspectRatio = 1.0f;
			uint32_t m_ViewWidth = 800;
			uint32_t m_ViewHeight = 800;
			bool m_ZRotationEnabled = false;
			bool m_HandleWindowResizeEnabled = true;
			bool m_HandleKeyboardEventsFlag = true;

			OrthographicCameraBounds m_Bounds;
			OrthographicCamera m_Camera;

			glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
			float m_CameraTranslationSpeed = 10.0f;

			float m_CameraZRotation = 0.0f;
			float m_CameraZRotationSpeed = 180.0f;
		};
	}
}