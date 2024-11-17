#pragma once

#include "MABEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Tools {
	class MABENGINE_API TranslationModule {
	public:
		TranslationModule() = default;
		TranslationModule(const glm::vec3& pos, const glm::vec3& rotation, const glm::vec3& scale);
		
		~TranslationModule() = default;

		const std::string& GetID() const { return m_ID; }

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { 
			m_Position = position;
			ReCalculateLocalTranslation();
		}

		const glm::vec3& GetRotation() const { return m_Rotation; }
		glm::vec3 GetRotationInDegree() { return glm::vec3(glm::degrees(m_Rotation));}
		void SetRotationInDegree(const glm::vec3& rotationInDegree) 
		{
			m_Rotation = glm::vec3(glm::radians(rotationInDegree));
			ReCalculateLocalTranslation();
		}

		const glm::vec3& GetScale() const { return m_Scale; }
		void SetScale(const glm::vec3& scale) { 
			m_Scale = scale; 
			ReCalculateLocalTranslation();
		}

		glm::mat4 GetLocalTranslation();

		glm::mat4 GetGlobalTranslation();

		void SetParent(TranslationModule* parent);

		void AddChild(TranslationModule* child) {
			m_Children.push_back(child);

			child->SetParent(this);
		}
		void RemoveChild(const std::string& id) {

			for (auto item = m_Children.begin(); item != m_Children.end(); ) {
				
				if ((*item)->GetID() == id) {
					m_Children.erase(item);
					break;
				}

				item++;
			}
		}

		void ReCalculateGlobalTranslation();
	private:
		void ReCalculateLocalTranslation();
		void UpdateChildrenTranslation();
	private:
		std::string m_ID = MABCore::EngineUUID::GenerateUUIDString();

		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);

		glm::mat4 m_LocalTranslation = glm::mat4(1.0f);
		glm::mat4 m_GlobalTranslation = glm::mat4(1.0f);

		TranslationModule* m_Parent = nullptr;
		std::vector<TranslationModule*> m_Children;


	};
}
