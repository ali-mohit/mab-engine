#include "mabengine_pch.h"

#include "Tools/TranslationModule.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace Tools {
	TranslationModule::TranslationModule(const glm::vec3& pos, const glm::vec3& rotation, const glm::vec3& scale)
		:m_Position(pos), m_Rotation(rotation), m_Scale(scale)
	{
		ReCalculateLocalTranslation();
	}
	glm::mat4 TranslationModule::GetLocalTranslation()
	{
		
		return m_LocalTranslation;
	}
	glm::mat4 TranslationModule::GetGlobalTranslation()
	{
		return m_GlobalTranslation;
	}
	void TranslationModule::SetParent(TranslationModule* parent)
	{
		auto oldParent = m_Parent;

		auto childWorldTranslation = GetGlobalTranslation();

		glm::mat4 parentGlobalTranslation = glm::mat4(1.0f);
		if (parent != nullptr)
			parentGlobalTranslation = parent->GetGlobalTranslation();

		m_LocalTranslation = glm::inverse(parentGlobalTranslation) * childWorldTranslation;

		// Step 3: Decompose the new local matrix to extract translation, rotation, and scale
		glm::vec3 scale, translation, skew;
		glm::quat rotation;
		glm::vec4 perspective;
		glm::decompose(m_LocalTranslation, scale, rotation, translation, skew, perspective);

		// Convert the rotation quaternion back to Euler angles (in radians)
		glm::vec3 eulerRotation = glm::eulerAngles(rotation);

		// Step 4: Update the child's transformation to keep its world position unchanged
		m_Position = translation;
		m_Rotation = eulerRotation;
		m_Scale = scale;

		m_Parent = parent;

		if (oldParent != nullptr)
			oldParent->RemoveChild(GetID());

		ReCalculateGlobalTranslation();
	}

	void TranslationModule::ReCalculateLocalTranslation()
	{
		// Create quaternion for pitch rotation
		//glm::quat pitchQuat = glm::angleAxis(m_Rotation[0], glm::vec3(1.0f, 0.0f, 0.0f));

		// Create quaternion for yaw rotation
		//glm::quat yawQuat = glm::angleAxis(m_Rotation[1], glm::vec3(0.0f, 1.0f, 0.0f));

		// Create quaternion for yaw rotation
		//glm::quat rollQuat = glm::angleAxis(m_Rotation[2], glm::vec3(0.0f, 0.0f, 1.0f));


		// Combine the three rotations
		//auto rotationQuat = glm::normalize(rollQuat * yawQuat * pitchQuat);

		//region technique01
		// Calculate rotation quaternion from Euler angles (pan, tilt, roll)
		glm::quat rotationQuat = glm::quat(m_Rotation);

		// Build rotation matrix from quaternion
		glm::mat4 rotationMatrix = glm::toMat4(rotationQuat);
		//endregion

		//auto rotationMatrix = glm::eulerAngleXYZ(m_Rotation[0], m_Rotation[1], m_Rotation[2]);

		
		// Build scale matrix
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_Scale);

		// Translate based on pivot
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_Position);

		// Final local transform = translation * rotation * scale
		m_LocalTranslation = translationMatrix * rotationMatrix * scaleMatrix;

		ReCalculateGlobalTranslation();
	}
	void TranslationModule::ReCalculateGlobalTranslation()
	{
		if (m_Parent)
			m_GlobalTranslation = m_Parent->GetGlobalTranslation() * m_LocalTranslation;
		else
			m_GlobalTranslation = m_LocalTranslation;

		UpdateChildrenTranslation();
	}
	void TranslationModule::UpdateChildrenTranslation()
	{
		for (auto item : m_Children) {
			item->ReCalculateGlobalTranslation();
		}
	}
}