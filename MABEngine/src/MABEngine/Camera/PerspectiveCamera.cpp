#include "mabengine_pch.h"
#include "PerspectiveCamera.h"


namespace MABEngine {

	namespace Camera {


		Camera::PerspectiveCamera::PerspectiveCamera()
		{
			RecalculateProjection();
			RecalculateView();
			RecalculateViewProjection();
		}
		
		PerspectiveCamera::PerspectiveCamera(const CameraSpecification& spec) :
			m_InputSpec(spec),
			m_CameraType(spec.CameraType), m_VerticalFOV(spec.VerticalFOV), m_FarClip(spec.FarClip), m_NearClip(spec.NearClip),
			m_ViewportWidth(spec.ViewportWidth), m_ViewportHeight(spec.ViewportHeight),
			m_Position(spec.Position), m_Target(spec.Target), m_UpDirection(spec.UpDirection),
			m_ForwardDirection(spec.ForwardDirection),
			m_Tilt(spec.CameraRotation.Tilt), m_Pan(spec.CameraRotation.Pan), m_Roll(spec.CameraRotation.Roll),
			m_Distance(spec.Distance)
		{
			RecalculateView();
			RecalculateProjection();
			RecalculateViewProjection();
		}

		void PerspectiveCamera::Resize(uint32_t width, uint32_t height)
		{
			m_ViewportWidth = width;
			m_ViewportHeight = height;

			RecalculateProjection();
			RecalculateViewProjection();
		}

		void PerspectiveCamera::PanAndTiltRotation(float pan, float tilt)
		{
			InnerRotation(pan, tilt, 0.0f);
		}

		void PerspectiveCamera::RollRotation(float roll)
		{
			InnerRotation(0, 0, roll);
		}

		void PerspectiveCamera::MoveDolly(float delta)
		{
			if (delta == 0)
				return;

			delta = delta * m_FarDirection;
			
			if (m_CameraType == CameraTypeEnum::FreeCamera) {
				m_Position = m_Position + (m_ForwardDirection * delta);
				m_Target = m_Target + (m_ForwardDirection * delta);
			}
			else if (m_CameraType == CameraTypeEnum::TargetCamera) {

				auto oldDirection = m_ForwardDirection;
				if(m_Distance < std::abs(delta))
					m_Position = m_Target + (m_ForwardDirection * delta);
				else
					m_Position = m_Position + (m_ForwardDirection * delta);

				m_Distance = glm::distance(m_Target, m_Position);
				
				//Change The Direction
				if (glm::dot((m_Target - m_Position), oldDirection) < 0)
				{
					m_ForwardDirection = -m_ForwardDirection;
					m_Pan += 180.0f;
					m_FarDirection *= -1;
				}
			}

			RecalculateView();
			RecalculateViewProjection();
		}

		void PerspectiveCamera::TruckAndPedestalMovement(float truckValue, float pedestalValue)
		{
			truckValue = std::abs(truckValue) < MIN_MOVEMENT_VALUE ? 0 : truckValue;
			pedestalValue = std::abs(pedestalValue) < MIN_MOVEMENT_VALUE ? 0 : pedestalValue;

			if (truckValue == 0 && pedestalValue == 0)
				return;
			
			m_Position = m_Position + (m_RightDirection * truckValue);
			m_Target = m_Target + (m_RightDirection * truckValue);

			m_Position = m_Position + (m_UpDirection * pedestalValue);
			m_Target = m_Target + (m_UpDirection * pedestalValue);

			RecalculateView();
			RecalculateViewProjection();
		}

		void PerspectiveCamera::ZoomCamera(float delta)
		{
			if (delta == 0) return;

			auto newVerticalFov = m_VerticalFOV + delta;

			if (newVerticalFov < 1.0f || newVerticalFov > 165)
				return;

			m_VerticalFOV = newVerticalFov;

			RecalculateProjection();
			RecalculateViewProjection();
		}

		void PerspectiveCamera::InnerRotation(float pan, float tilt, float roll)
		{
			if (std::abs(pan) == MIN_ROTATIO_VALUE && std::abs(tilt) <= MIN_ROTATIO_VALUE && std::abs(roll) == MIN_ROTATIO_VALUE)
				return;

			m_Pan += -pan;
			m_Tilt += -tilt;
			m_Roll += -roll;

			// Constrain the pitch
			if (m_Tilt > 360.0f)
				m_Tilt -= 360.0f;
			if (m_Tilt < -360.f)
				m_Tilt += 360.0f;

			// Normalize the angles to avoid overflow
			if (m_Pan > 360.0f)
				m_Pan -= 360.0f;
			else if (m_Pan < -360.0f)
				m_Pan += 360.0f;

			// Normalize the angles to avoid overflow
			if (m_Roll > 360.0f)
				m_Roll -= 360.0f;
			else if (m_Roll < -360.0f)
				m_Roll += 360.0f;

			// Create quaternion for pitch rotation
			//glm::quat pitchQuat = glm::angleAxis(glm::radians(m_Tilt), glm::vec3(1.0f, 0.0f, 0.0f));

			// Create quaternion for yaw rotation
			//glm::quat yawQuat = glm::angleAxis(glm::radians(m_Pan), glm::vec3(0.0f, 1.0f, 0.0f));

			// Create quaternion for yaw rotation
			//glm::quat rollQuat = glm::angleAxis(glm::radians(m_Roll), glm::vec3(0.0f, 0.0f, 1.0f));


			// Combine the three rotations
			//auto orientation = glm::normalize(rollQuat * yawQuat * pitchQuat);
			auto orientation = glm::quat(glm::vec3(glm::radians(m_Tilt), glm::radians(m_Pan), glm::radians(m_Roll)));

			// Update the forward direction
			m_ForwardDirection = glm::normalize(glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f)));
			m_RightDirection = glm::normalize(glm::rotate(orientation, glm::vec3(1.0f, 0.0f, 0.0f)));
			m_UpDirection = glm::normalize(glm::rotate(orientation, glm::vec3(0.0f, 1.0f, 0.0f)));

			// Recalculate the Right and Up vector
			//m_RightDirection = glm::normalize(glm::cross(m_ForwardDirection, WORLD_UP));
			//m_UpDirection = glm::normalize(glm::cross(m_RightDirection, m_ForwardDirection));

			if (m_CameraType == CameraTypeEnum::TargetCamera)
				m_Position = m_Target + (-m_ForwardDirection * m_Distance);
			else
				m_Target = m_Position + (m_ForwardDirection * m_Distance);

			RecalculateView();
			RecalculateViewProjection();
		}

		void PerspectiveCamera::RecalculateProjection()
		{
			m_Projection = glm::perspective(
				glm::radians(m_VerticalFOV),
				(float)m_ViewportWidth / (float)m_ViewportHeight,
				m_NearClip,
				m_FarClip
			);
			m_InverseProjection = glm::inverse(m_Projection);

		}

		void PerspectiveCamera::RecalculateView()
		{
			m_View = glm::lookAt(m_Position, m_Position + m_ForwardDirection, m_UpDirection);
			m_InverseView = glm::inverse(m_View);
		}

		void PerspectiveCamera::RecalculateViewProjection()
		{
			m_ViewProjectionMatrix = m_Projection * m_View;
			m_InverseViewProjectionMatrix = glm::inverse(m_ViewProjectionMatrix);
		}

	}
}