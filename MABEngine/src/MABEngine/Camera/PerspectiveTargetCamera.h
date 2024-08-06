#pragma once

#include "MABEngine/Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp> // Ensure this is included for quaternion rotation


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

			float m_Distance = 10;

			float m_VerticalFOV = 45.0f;
			float m_NearClip = 0.1f;
			float m_FarClip = 100.0f;

			uint32_t m_ViewportWidth = 1280;
			uint32_t m_ViewportHeight = 720;

			glm::quat m_Orientation;

			float m_Yaw = 0.0f;
			float m_Pitch = 0.0f;

			static constexpr glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f); // WORLD_UP definition
		};

	}
}