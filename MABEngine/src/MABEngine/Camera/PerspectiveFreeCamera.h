#pragma once
#include "MABEngine/Core/Base.h"

#include <glm/glm.hpp>

namespace MABEngine {

	namespace Camera {
		class MABENGINE_API PerspectiveFreeCamera
		{
		public:
			PerspectiveFreeCamera();
			PerspectiveFreeCamera(float verticalFOV, float nearClip, float farClip);

			void OnResize(uint32_t width, uint32_t height);

			const glm::mat4& GetProjection() const { return m_Projection; }
			const glm::mat4& GetInverseProjection() const { return m_InverseProjection; }
			const glm::mat4& GetView() const { return m_View; }
			const glm::mat4& GetInverseView() const { return m_InverseView; }
			const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
			const glm::mat4& GetInverseViewProjectionMatrix() const { return m_InverseViewProjectionMatrix; }

			const glm::vec3& GetPosition() const { return m_Position; }
			void SetPosition(const glm::vec3& pos) { m_Position = pos; RecalculateView(); }

			const glm::vec3& GetDirection() const { return m_ForwardDirection; }
			void SetForwardDirection(const glm::vec3& direction) { m_ForwardDirection = direction; RecalculateView(); }

		private:
			void RecalculateProjection();
			void RecalculateView();
			void RecalculateViewProjection();
		private:
			glm::mat4 m_Projection{ 1.0f };
			glm::mat4 m_View{ 1.0f };
			glm::mat4 m_ViewProjectionMatrix{ 1.0f };

			glm::mat4 m_InverseProjection{ 1.0f };
			glm::mat4 m_InverseView{ 1.0f };
			glm::mat4 m_InverseViewProjectionMatrix{ 1.0f };

			float m_VerticalFOV = 45.0f;
			float m_NearClip = 0.1f;
			float m_FarClip = 100.0f;

			glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
			glm::vec3 m_ForwardDirection{ 0.0f, 0.0f, 0.0f };

			uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		};
	}
}
