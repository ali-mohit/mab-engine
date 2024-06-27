#include "mabengine_pch.h"
#include "MABEngine/Core/Base.h"
#include "MABEngine/Logging/Log.h"
#include "MABEngine/Camera/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace MABEngine {

	namespace Camera {
		
		OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
			:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
		{
			MAB_PROFILE_FUNCTION();

			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

		OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar)
			:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, zNear, zFar)), m_ViewMatrix(1.0f)
		{
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}
		
		void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
		{
			MAB_PROFILE_FUNCTION();

			m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

		void OrthographicCamera::SetProjection(float left, float right, float bottom, float top, float zNear, float zFar)
		{
			MAB_PROFILE_FUNCTION();

			m_ProjectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}


		void OrthographicCamera::RecalculateViewMatrix()
		{
			MAB_PROFILE_FUNCTION();

			glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
				glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationZ), glm::vec3(0, 0, 1));

			m_ViewMatrix = glm::inverse(transform);
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}
	}
}