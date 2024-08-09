#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Camera/CameraTypeEnum.h"
#include "MABEngine/Camera/Utilities.h"

#include <glm/glm.hpp>


namespace MABEngine {

	namespace Camera {
		struct MABENGINE_API CameraSpecification {
			CameraTypeEnum CameraType = CameraTypeEnum::FreeCamera;

			float VerticalFOV = 45.0f;
			float NearClip = 0.1f;
			float FarClip = 100.0f;

			uint32_t ViewportWidth = 1280;
			uint32_t ViewportHeight = 720;

			glm::vec3 Position = { 0.0f, 0.0f, 10.0f };
			glm::vec3 Target = { 0.0f, 0.0f, 0.0f };
			glm::vec3 UpDirection = { 0.0f, 1.0f, 0.0f };

			glm::vec3 ForwardDirection = {0.0f, 0.0f, -1.0f};

			CameraRotation CameraRotation;
			
			float Distance = 1.0f;

			CameraSpecification() = default;
			
			static CameraSpecification CreateFreeCam(
				float fov, float nearClip, float farClip,
				uint32_t w, uint32_t h,
				glm::vec3 pos = {0.0f, 0.0f, 0.0f}, 
				glm::vec3 forwardDirection = { 0.0f, 0.0f, -1.0f},
				glm::vec3 up = {0.0f, 1.0f, 0.0f})
			{
				CameraSpecification result;

				result.CameraType = CameraTypeEnum::FreeCamera;

				result.VerticalFOV = fov;
				result.NearClip = nearClip;
				result.FarClip = farClip;

				result.ViewportWidth = w;
				result.ViewportHeight = h;

				result.Position = pos;
				result.ForwardDirection = glm::normalize(forwardDirection);
				result.UpDirection = glm::normalize(up);

				result.Target = pos + forwardDirection;

				result.CameraRotation = CalculateCameraAngles(result.ForwardDirection, result.UpDirection);

				result.Distance = 1.0f;
				
				return result;
			}
			
			static CameraSpecification CreateTargetCamera(
				float fov, float nearClip, float farClip,
				uint32_t w, uint32_t h,
				glm::vec3 pos, glm::vec3 target, glm::vec3 up)
			{
				CameraSpecification result;

				result.CameraType = CameraTypeEnum::TargetCamera;

				result.VerticalFOV = fov;
				result.NearClip = nearClip;
				result.FarClip = farClip;

				result.ViewportWidth = w;
				result.ViewportHeight = h;

				result.Position = pos;
				result.Target = target;
				result.UpDirection = up;
				result.Distance = glm::distance(target, pos);

				result.ForwardDirection = glm::normalize(target - pos);

				result.CameraRotation = CalculateCameraAngles(result.ForwardDirection, result.UpDirection);

				return result;
			}

		};
	}
}

