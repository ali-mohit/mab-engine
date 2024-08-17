#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Camera/CameraTypeEnum.h"
#include "MABEngine/Camera/CameraSpecification.h"

#define GLM_ENABLE_EXPERIMENTAL
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

namespace MABEngine {

	namespace Camera {

		class MABENGINE_API PerspectiveCamera {
		public:
			PerspectiveCamera();
			PerspectiveCamera(const CameraSpecification& spec);
			~PerspectiveCamera() = default;

			void Resize(uint32_t width, uint32_t height);

			/// <summary>
			/// Pitch (Tilt): Rotation around the lateral (X) axis. This rotation changes the direction the camera is pointing vertically.
			/// Yaw (Pan): Rotation around the vertical (Y) axis. This rotation changes the direction the camera is pointing horizontally.
			/// </summary>
			/// <param name="x">value is given in degrees.</param>
			/// <param name="y">value is given in degrees.</param>
			void LocalXYRotation(float x, float y) { return PanAndTiltRotation(x, y); }
			/// <summary>
			/// Pitch (Tilt): Rotation around the lateral (X) axis. This rotation changes the direction the camera is pointing vertically.
			/// Yaw (Pan): Rotation around the vertical (Y) axis. This rotation changes the direction the camera is pointing horizontally.
			/// </summary>
			/// <param name="tilt">value is given in degrees.</param>
			/// <param name="pan">value is given in degrees.</param>
			void PanAndTiltRotation(float pan, float tilt);

			/// <summary>
			/// Rotation around the longitudinal (Z) axis.
			/// This rotation tilts the camera side-to-side, changing the horizon line.
			/// </summary>
			/// <param name="z">value is given in degrees.</param>
			void LocalZRotation(float z) { return RollRotation(z); }
			/// <summary>
			/// Rotation around the longitudinal (Z) axis.
			/// This rotation tilts the camera side-to-side, changing the horizon line.
			/// </summary>
			/// <param name="roll">value is given in degrees.</param>
			void RollRotation(float roll);

			/// <summary>
			/// oving the camera linearly along the Z-axis
			/// </summary>
			/// <param name="delta"></param>
			void MoveTowardTarget(float delta) { return MoveDolly(delta); };
			/// <summary>
			/// Dolly movement involves moving the camera linearly along the Z-axis, either
			/// forward (toward the subject) or backward (away from the subject).
			/// This is often achieved by placing the camera on a dolly, a wheeled platform that rolls along a track.
			/// </summary>
			/// <param name="delta"></param>
			void MoveDolly(float delta);

			/// <summary>
			/// moving the camera horizontally left or right and moving the camera vertically up or down
			/// </summary>
			/// <param name="x"></param>
			/// <param name="y"></param>
			void LocalXYMovement(float x, float y) { return TruckAndPedestalMovement(x, y); }
			/// <summary>
			/// The truck movement involves moving the camera horizontally left or right,
			/// while maintaining its direction toward the subject. This movement is similar to the camera
			/// being mounted on a dolly (a wheeled platform) that rolls left or right.
			/// 
			/// Pedestal movement refers to moving the camera vertically up or down,
			/// while keeping its direction constant. The camera "pedestals" without tilting its angle.
			/// </summary>
			/// <param name="truckValue">camera horizontally left or right value</param>
			/// <param name="pedestalValue">camera vertically up or down value</param>
			void TruckAndPedestalMovement(float truckValue, float pedestalValue);

			void ZoomCamera(float delta);
		
		public:
			const CameraSpecification& GetCameraSetupSpecification() const { return m_InputSpec; }

			const glm::mat4& GetProjection() const { return m_Projection; }
			const glm::mat4& GetInverseProjection() const { return m_InverseProjection; }
			const glm::mat4& GetView() const { return m_View; }
			const glm::mat4& GetInverseView() const { return m_InverseView; }
			const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
			const glm::mat4& GetInverseViewProjectionMatrix() const { return m_InverseViewProjectionMatrix; }

			const glm::vec3& GetPosition() const { return m_Position; }

			const glm::vec3& GetDirection() const { return m_ForwardDirection; }
			const glm::vec3& GetUpDirection() const { return m_UpDirection; }

			float GetVerticalFOV() { return m_VerticalFOV; }
			float GetNearClip() { return m_NearClip; }
			float GetFarClip() { return m_FarClip; }

			uint32_t GetViewportWidth() { return m_ViewportWidth; }
			uint32_t GetViewportHeight() { return m_ViewportHeight; }
			std::pair<uint32_t, uint32_t> GetViewportSize() { return { m_ViewportWidth, m_ViewportHeight }; }
		
		private:
			void InnerRotation(float pan, float tilt, float roll);
			void RecalculateProjection();
			void RecalculateView();
			void RecalculateViewProjection();

		public:
			static constexpr glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f); // WORLD_UP definition

			static constexpr float MIN_ROTATIO_VALUE = 0.5;
			static constexpr float MIN_MOVEMENT_VALUE = 0.1;
		private:
			CameraSpecification m_InputSpec;

			CameraTypeEnum m_CameraType = CameraTypeEnum::FreeCamera;
			float m_Distance = 1;

			float m_VerticalFOV = 45.0f;
			float m_NearClip = 0.01f;
			float m_FarClip = 100.0f;

			uint32_t m_ViewportWidth = 1280;
			uint32_t m_ViewportHeight = 720;

			glm::vec3 m_ForwardDirection = { 0.0f, 0.0f, -1.0f };
			glm::vec3 m_UpDirection = { 0.0f, 1.0f, 0.0f };
			glm::vec3 m_RightDirection = { 1.0f, 0.0f, 0.0f };

			glm::vec3 m_Target = { 0.0f, 0.0f, 0.0f };
			glm::vec3 m_Position = { 0.0f, 0.0f, 10.0f };

			glm::mat4 m_Projection{ 1.0f };
			glm::mat4 m_View{ 1.0f };
			glm::mat4 m_ViewProjectionMatrix{ 1.0f };

			glm::mat4 m_InverseProjection{ 1.0f };
			glm::mat4 m_InverseView{ 1.0f };
			glm::mat4 m_InverseViewProjectionMatrix{ 1.0f };

			float m_Tilt = 0.0f;
			float m_Pan = 0.0f;
			float m_Roll = 0.0f;
			float m_FarDirection = 1.0f;
		};

	}
}
