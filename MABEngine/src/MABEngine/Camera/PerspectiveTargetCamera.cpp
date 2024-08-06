#include "mabengine_pch.h"
#include "MABEngine/Camera/PerspectiveTargetCamera.h"


namespace MABEngine {

	namespace Camera {
		PerspectiveTargetCamera::PerspectiveTargetCamera()
		{
			RecalculateAxises();
			RecalculateProjection();
			RecalculateView();
		}
		
		PerspectiveTargetCamera::PerspectiveTargetCamera(float nearClip, float farClip, float verticalFOV):
			m_NearClip(nearClip), m_FarClip(farClip), m_VerticalFOV(verticalFOV)
		{
			RecalculateAxises();
			RecalculateProjection();
			RecalculateView();
			
		}

		PerspectiveTargetCamera::PerspectiveTargetCamera(
			float nearClip, float farClip, float verticalFOV,
			uint32_t width, uint32_t height
		)
			:m_NearClip(nearClip), m_FarClip(farClip), m_VerticalFOV(verticalFOV),
			m_ViewportWidth(width), m_ViewportHeight(height)
		{
			RecalculateAxises();
			RecalculateProjection();
			RecalculateView();
		}

		PerspectiveTargetCamera::PerspectiveTargetCamera(
			float nearClip, float farClip, float verticalFOV,
			uint32_t width, uint32_t height,
			const glm::vec3& cameraPos, const glm::vec3& cameraTarget
		)
			:m_NearClip(nearClip), m_FarClip(farClip), m_VerticalFOV(verticalFOV), 
			m_Position(cameraPos), m_Target(cameraTarget),
			m_ViewportWidth(width), m_ViewportHeight(height)
		{
			RecalculateAxises();
			RecalculateProjection();
			RecalculateView();
		}

		PerspectiveTargetCamera::PerspectiveTargetCamera(
			float nearClip, float farClip, float verticalFOV,
			uint32_t width, uint32_t height,
			const glm::vec3& cameraPos, const glm::vec3& cameraTarget, const glm::vec3& upDirection
		) 
			:m_NearClip(nearClip), m_FarClip(farClip), m_VerticalFOV(verticalFOV),
			m_Position(cameraPos), m_Target(cameraTarget),
			m_ViewportWidth(width), m_ViewportHeight(height), m_UpDirection(upDirection)

		{
			RecalculateAxises();
			RecalculateProjection();
			RecalculateView();
			
		}

		
		void PerspectiveTargetCamera::OnResize(uint32_t width, uint32_t height)
		{
			if (width == m_ViewportWidth && height == m_ViewportHeight)
				return;

			m_ViewportWidth = width;
			m_ViewportHeight = height;

			RecalculateProjection();
		}


		void PerspectiveTargetCamera::RotateAroundTargetLocal(float yaw, float pitch)
		{
			if (yaw == 0 && pitch == 0)
				return;

			m_Yaw += yaw;
			m_Pitch += pitch;

			// Constrain the pitch
			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;

			// Normalize the angles to avoid overflow
			if (m_Yaw > 360.0f)
				m_Yaw -= 360.0f;
			else if (m_Yaw < -360.0f)
				m_Yaw += 360.0f;

			// Create quaternion for pitch rotation
			glm::quat pitchQuat = glm::angleAxis(glm::radians(m_Pitch), glm::vec3(1.0f, 0.0f, 0.0f));

			// Create quaternion for yaw rotation
			glm::quat yawQuat = glm::angleAxis(glm::radians(m_Yaw), glm::vec3(0.0f, 1.0f, 0.0f));

			// Combine the two rotations
			m_Orientation = glm::normalize(yawQuat * pitchQuat);

			// Update the forward direction
			m_ForwardDirection = glm::normalize(glm::rotate(m_Orientation, glm::vec3(0.0f, 0.0f, -1.0f)));

			// Recalculate the Right and Up vector
			m_RightDirection = glm::normalize(glm::cross(m_ForwardDirection, WORLD_UP));
			m_UpDirection = glm::normalize(glm::cross(m_RightDirection, m_ForwardDirection));

			m_Position = m_Target + (-m_ForwardDirection * m_Distance);

			RecalculateView();
		}

		void PerspectiveTargetCamera::MoveTowardTarget(float delta)
		{
			// Calculate the local axes
			m_Position += m_ForwardDirection * delta;
			m_Distance = glm::distance(m_Position, m_Target);

			if (m_Position == m_Target) {
				m_Position += m_ForwardDirection * 0.01f;
				m_ForwardDirection = -m_ForwardDirection;
				m_UpDirection = -m_UpDirection;
				m_RightDirection = -m_RightDirection;
				m_Distance = 0.01f;
			}

			/*if (delta >= distance) {
				m_UpDirection = -m_UpDirection;
			}*/
			
			RecalculateView();
		}

		void PerspectiveTargetCamera::RecalculateProjection()
		{
			m_Projection = glm::perspectiveFov(
				glm::radians(m_VerticalFOV),
				(float)m_ViewportWidth,
				(float)m_ViewportHeight,
				m_NearClip,
				m_FarClip
			);
			m_InverseProjection = glm::inverse(m_Projection);

			m_ViewProjectionMatrix = m_Projection * m_View;
			m_InverseViewProjectionMatrix = glm::inverse(m_ViewProjectionMatrix);
		}

		void PerspectiveTargetCamera::RecalculateView()
		{
			m_View = glm::lookAt(m_Position, m_ForwardDirection, m_UpDirection);
			m_InverseView = glm::inverse(m_View);


			m_ViewProjectionMatrix = m_Projection * m_View;
			m_InverseViewProjectionMatrix = glm::inverse(m_ViewProjectionMatrix);
		}

		void PerspectiveTargetCamera::RecalculateViewProjection()
		{
			m_ViewProjectionMatrix = m_Projection * m_View;
			m_InverseViewProjectionMatrix = glm::inverse(m_ViewProjectionMatrix);
		}

		void PerspectiveTargetCamera::RecalculateAxises()
		{
			m_Distance = glm::distance(m_Target, m_Position);
			m_ForwardDirection = glm::normalize(m_Target - m_Position);
			m_RightDirection = glm::normalize(glm::cross(m_ForwardDirection, m_UpDirection));

		}
	}
}