#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Components/TagComponent.h"
#include "MABEngine/Components/IDComponent.h"
#include "MABEngine/Scene/SceneManagement.h"

#include <entt.hpp>

namespace MABEngine {
	namespace Scene {
		class MABENGINE_API Entity {
		public:
			Entity() = default;
			Entity(entt::entity handle, SceneManagement* scene);
			Entity(const Entity& other) = default;
			
			template<typename T>
			bool HasComponent() {
				return m_Repo->m_Registry.all_of<T>(m_EntityHandle);
			}

			template<typename T, typename... Args>
			T& AddComponent(Args&&... args)
			{
				MAB_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
				T& component = m_Repo->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
				m_Repo->OnComponentAdded<T>(*this, component);
				return component;
			}

			template<typename T, typename... Args>
			T& AddOrReplaceComponent(Args&&... args)
			{
				T& component = m_Repo->m_Registry.emplace_or_replace<T>(m_EntityHandle, std::forward<Args>(args)...);
				m_Repo->OnComponentAdded<T>(*this, component);
				return component;
			}

			template<typename T>
			T& GetComponent()
			{
				MAB_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
				return m_Repo->m_Registry.get<T>(m_EntityHandle);
			}

			template<typename T>
			void RemoveComponent()
			{
				MAB_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
				m_Repo->m_Registry.remove<T>(m_EntityHandle);
			}
		
		public:

			operator bool() const { return m_EntityHandle != entt::null; }
			operator entt::entity() const { return m_EntityHandle; }
			operator uint32_t() const { return (uint32_t)m_EntityHandle; }

			bool operator==(const Entity& other) const
			{
				return m_EntityHandle == other.m_EntityHandle && m_Repo == other.m_Repo;
			}

			bool operator!=(const Entity& other) const
			{
				return !(*this == other);
			}

			const std::string& GetScopeName() const { return m_Repo->GetScopeName(); }
			Core::EngineUUID GetUUID() { return GetComponent<Components::IDComponent>().ID; }
			const std::string& GetName() { return GetComponent<Components::TagComponent>().Tag; }
			const std::string& GetFullName() { 
				auto scopeName = m_Repo->GetScopeName();
				if (!scopeName.empty()) {
					scopeName = scopeName + "::";
				}
				return scopeName + GetComponent<Components::TagComponent>().Tag;
			}
		private:
			entt::entity m_EntityHandle{ entt::null };
			SceneManagement* m_Repo = nullptr;
		};

		
	}
}