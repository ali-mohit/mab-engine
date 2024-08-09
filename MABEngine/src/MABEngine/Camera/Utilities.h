#pragma once

#include <glm/glm.hpp>

namespace MABEngine {

	namespace Camera {

        struct CameraRotation {
            float Pan = 0.0f;
            float Tilt = 0.0f;
            float Roll = 0.0f;

            CameraRotation() = default;
            CameraRotation(float pan, float tilt, float roll):
                Pan(pan), Tilt(tilt), Roll(roll) {}
        };

		inline CameraRotation CalculateCameraAngles(
            const glm::vec3& cameraDirection,
            const glm::vec3& cameraUp
        ) {
            // Ensure the forward vector is normalized
            glm::vec3 normForward = glm::normalize(cameraDirection);

            // Calculate Yaw: the angle between the forward vector's projection onto the XZ plane and the Z axis
            float outPan = glm::degrees(atan2(-normForward.x, -normForward.z));

            // Calculate Pitch: the angle between the forward vector and the XZ plane
            float outTilt = glm::degrees(asin(normForward.y));

            // Calculate Right vector (cross product of Up and Forward)
            glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, normForward));

            // Calculate the local Up vector (cross product of Forward and Right)
            glm::vec3 localUp = glm::cross(normForward, cameraRight);

            // Calculate Roll: the angle between the world Up vector and the camera's local Up vector
            float outRoll = glm::degrees(atan2(glm::dot(cameraRight, cameraUp), glm::dot(localUp, cameraUp)));

            return CameraRotation(outPan, outTilt, outRoll);
		}
	}
}
