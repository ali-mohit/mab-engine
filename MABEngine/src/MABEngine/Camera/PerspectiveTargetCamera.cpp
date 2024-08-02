#include "mabengine_pch.h"
#include "MABEngine/Camera/PerspectiveTargetCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "glm/glm.hpp"

namespace MABEngine {

	namespace Camera {
		PerspectiveTargetCamera::PerspectiveTargetCamera()
		{
			RecalculateProjection();
			RecalculateView();
			RecalculateAxises();
		}
		
		PerspectiveTargetCamera::PerspectiveTargetCamera(float nearClip, float farClip, float verticalFOV):
			m_NearClip(nearClip), m_FarClip(farClip), m_VerticalFOV(verticalFOV)
		{
			RecalculateProjection();
			RecalculateView();
			RecalculateAxises();
		}

		PerspectiveTargetCamera::PerspectiveTargetCamera(
			float nearClip, float farClip, float verticalFOV,
			uint32_t width, uint32_t height
		)
			:m_NearClip(nearClip), m_FarClip(farClip), m_VerticalFOV(verticalFOV),
			m_ViewportWidth(width), m_ViewportHeight(height)
		{
			RecalculateProjection();
			RecalculateView();
			RecalculateAxises();
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
			RecalculateProjection();
			RecalculateView();
			RecalculateAxises();
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
			RecalculateProjection();
			RecalculateView();
			RecalculateAxises();
		}

		
		void PerspectiveTargetCamera::OnResize(uint32_t width, uint32_t height)
		{
			if (width == m_ViewportWidth && height == m_ViewportHeight)
				return;

			m_ViewportWidth = width;
			m_ViewportHeight = height;

			RecalculateProjection();
		}


		void PerspectiveTargetCamera::RotateAroundTargetLocal(float angleX, float angleY)
		{
			bool changed = false;
			
			if (angleX != 0) {
				m_ForwardDirection = glm::rotate(m_ForwardDirection, angleX, m_UpDirection);
				m_RightDirection = glm::rotate(m_RightDirection, angleX, m_UpDirection);
				changed = true;
			}

			if (angleY != 0) {
				m_ForwardDirection = glm::rotate(m_ForwardDirection, angleY, m_RightDirection);
				m_UpDirection = glm::rotate(m_UpDirection, angleY, m_RightDirection);
				changed = true;
			}
			
			
			
			if (changed) {
				m_Position = -m_Distance * m_ForwardDirection;

				RecalculateView();
			}
			
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
			m_Projection = glm::perspective(
				glm::radians(m_VerticalFOV),
				((float)m_ViewportWidth/ (float)m_ViewportHeight),
				m_NearClip,
				m_FarClip
			);
			m_InverseProjection = glm::inverse(m_Projection);

			m_ViewProjectionMatrix = m_Projection * m_View;
			m_InverseViewProjectionMatrix = glm::inverse(m_ViewProjectionMatrix);
		}

		void PerspectiveTargetCamera::RecalculateView()
		{
			m_View = glm::lookAt(m_Position, m_Target, m_UpDirection);
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