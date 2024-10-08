#pragma once

#include "MABEngine/Core/Base.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace MABEngine {
	namespace Components {

		struct MABENGINE_API TransformComponent
		{
			glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
			glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
			glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::vec3& translation)
				: Translation(translation) {}

			glm::mat4 GetTransform() const
			{
				glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

				return glm::translate(glm::mat4(1.0f), Translation)
					* rotation
					* glm::scale(glm::mat4(1.0f), Scale);
			}
		};

	}

}