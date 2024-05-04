#pragma once

#include <glm/glm.hpp>

#include "MABEngine/Core.h"


namespace MABEngine {

	namespace Renderer {
		class MABENGINE_API OrthographicCamera {
		public:
			OrthographicCamera(float left, float right, float bottom, float top);
			OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar);

			const glm::vec3& GetPosition() const { return m_Position; }
			void SetPosition(const glm::vec3& position) { m_Position = position;  RecalculateViewMatrix(); }

			float GetRotationZ() { return m_RotationZ; }
			void SetRotationZ(float rotation) { m_RotationZ = rotation; RecalculateViewMatrix(); }

			const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
			const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }
			const glm::mat4& getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

			void RecalculateViewMatrix();
		private:
			glm::mat4 m_ProjectionMatrix;
			glm::mat4 m_ViewMatrix;
			glm::mat4 m_ViewProjectionMatrix;

			glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
			float m_RotationZ = 0.0f;
		};
	}
}
