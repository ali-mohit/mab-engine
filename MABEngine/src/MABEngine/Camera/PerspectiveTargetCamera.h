#pragma once

#include "MABEngine/Core/Base.h"

#include <glm/glm.hpp>


namespace MABEngine {

	namespace Camera {

		class MABENGINE_API PerspectiveTargetCamera {
		public:
			PerspectiveTargetCamera();
			
			PerspectiveTargetCamera(
				float nearClip, float farClip, float verticalFOV
			);
			
			PerspectiveTargetCamera(
				float nearClip, float farClip, float verticalFOV,
				uint32_t width, uint32_t height
			);
			
			PerspectiveTargetCamera(
				float nearClip, float farClip, float verticalFOV, 
				uint32_t width, uint32_t height,
				const glm::vec3& cameraPos, const glm::vec3& cameraTarget
			);

			PerspectiveTargetCamera(
				float nearClip, float farClip, float verticalFOV,
				uint32_t width, uint32_t height,
				const glm::vec3& cameraPos, const glm::vec3& cameraTarget, const glm::vec3& upDirection
			);

			~PerspectiveTargetCamera() = default; 

			void OnResize(uint32_t width, uint32_t height);

			void RotateAroundTargetLocal(float angleX, float angleY);

			void MoveTowardTarget(float delta);

			//Change the pitch (up, down) for the free camera
			void ChangePitch(float degrees);

			//Change heading (left, right) for the free camera
			void ChangeHeading(float degrees);

			const glm::mat4& GetProjection() const { return m_Projection; }
			const glm::mat4& GetInverseProjection() const { return m_InverseProjection; }
			const glm::mat4& GetView() const { return m_View; }
			const glm::mat4& GetInverseView() const { return m_InverseView; }
			const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
			const glm::mat4& GetInverseViewProjectionMatrix() const { return m_InverseViewProjectionMatrix; }

			const glm::vec3& GetPosition() const { return m_Position; }

			const glm::vec3& GetDirection() const { return glm::normalize(m_Target - m_Position); }
			const glm::vec3& GetUpDirection() const { return m_UpDirection; }

			float GetVerticalFOV() { return m_VerticalFOV; }
			float GetNearClip() { return m_NearClip; }
			float GetFarClip() { return m_FarClip; }

		private:
			void RecalculateProjection();
			void RecalculateView();
			void RecalculateViewProjection();
			void RecalculateAxises();
		private:
			glm::mat4 m_Projection{ 1.0f };
			glm::mat4 m_View{ 1.0f };
			glm::mat4 m_ViewProjectionMatrix{ 1.0f };

			glm::mat4 m_InverseProjection{ 1.0f };
			glm::mat4 m_InverseView{ 1.0f };
			glm::mat4 m_InverseViewProjectionMatrix{ 1.0f };


			glm::vec3 m_UpDirection = { 0.0f, 1.0f, 0.0f };
			glm::vec3 m_RightDirection = { 1.0f, 0.0f, 0.0f };
			glm::vec3 m_ForwardDirection = { 0.0f, 0.0f, 0.0f };
			glm::vec3 m_Target = { 0.0f, 0.0f, 0.0f };
			glm::vec3 m_Position = { 0.0f, 0.0f, 10.0f };

			float m_Distance = 0;

			float m_VerticalFOV = 45.0f;
			float m_NearClip = 0.1f;
			float m_FarClip = 100.0f;

			uint32_t m_ViewportWidth = 1280;
			uint32_t m_ViewportHeight = 720;

			float camera_heading = 0.0f;
			float camera_pitch = 0.0f;
		};

	}
}