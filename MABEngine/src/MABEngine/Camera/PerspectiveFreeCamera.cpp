#include "mabengine_pch.h"

#include "MABEngine/Core/Base.h"
#include "MABEngine/Camera/PerspectiveFreeCamera.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "glm/glm.hpp"


namespace MABEngine {

	namespace Camera {
		PerspectiveFreeCamera::PerspectiveFreeCamera()
			: m_VerticalFOV(45.0f), m_NearClip(0.1f), m_FarClip(100.0f)
		{
			m_ForwardDirection = glm::vec3(0, 0, -1);
			m_Position = glm::vec3(0, 0, 6);
		}

		PerspectiveFreeCamera::PerspectiveFreeCamera(float verticalFOV, float nearClip, float farClip)
			: m_VerticalFOV(verticalFOV), m_NearClip(nearClip), m_FarClip(farClip)
		{
			m_ForwardDirection = glm::vec3(0, 0, -1);
			m_Position = glm::vec3(0, 0, 6);
		}

		void PerspectiveFreeCamera::OnResize(uint32_t width, uint32_t height)
		{
			if (width == m_ViewportWidth && height == m_ViewportHeight)
				return;

			m_ViewportWidth = width;
			m_ViewportHeight = height;

			RecalculateProjection();
		}

		void PerspectiveFreeCamera::RecalculateProjection()
		{
			m_Projection = glm::perspectiveFov(glm::radians(m_VerticalFOV), (float)m_ViewportWidth, (float)m_ViewportHeight, m_NearClip, m_FarClip);
			m_InverseProjection = glm::inverse(m_Projection);

			RecalculateViewProjection();
		}

		void PerspectiveFreeCamera::RecalculateView()
		{
			m_View = glm::lookAt(m_Position, m_Position + m_ForwardDirection, glm::vec3(0, 1, 0));
			m_InverseView = glm::inverse(m_View);

			RecalculateViewProjection();
		}

		void PerspectiveFreeCamera::RecalculateViewProjection()
		{
			m_ViewProjectionMatrix = m_Projection * m_View;
			m_InverseViewProjectionMatrix = glm::inverse(m_ViewProjectionMatrix);
		}

	}
}