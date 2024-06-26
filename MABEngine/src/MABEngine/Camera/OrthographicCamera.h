#pragma once
#include "MABEngine/Core/Base.h"

#include <glm/glm.hpp>


namespace MABEngine {

	namespace Camera {
		class MABENGINE_API OrthographicCamera {
		public:
			OrthographicCamera(float left, float right, float bottom, float top);
			OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar);

			void SetProjection(float left, float right, float bottom, float top);
			void SetProjection(float left, float right, float bottom, float top, float zNear, float zFar);

			const glm::vec3& GetPosition() const { return m_Position; }
			void SetPosition(const glm::vec3& position) { 
				m_Position = { position.x, position.y, position.z };  
				RecalculateViewMatrix(); 
			}

			float GetRotationZ() { return m_RotationZ; }
			void SetRotationZ(float rotation) { m_RotationZ = rotation; RecalculateViewMatrix(); }

			const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
			const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
			const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		private:
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
