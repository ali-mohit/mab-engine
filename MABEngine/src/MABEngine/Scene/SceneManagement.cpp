#include "mabengine_pch.h"
#include "MABEngine/Scene/SceneManagement.h"

#include "MABEngine/Core/Base.h"
#include "MABEngine/Core/EngineUUID.h"

#include "MABEngine/Components/IDComponent.h"
#include "MABEngine/Components/TagComponent.h"
#include "MABEngine/Components/TextComponent.h"
#include "MABEngine/Components/SpriteRendererComponent.h"
#include "MABEngine/Components/ComponentGroup.h"

#include "MABEngine/Scene/Utilities.h"

namespace MABEngine {
	namespace Scene {
		
		SceneManagement::SceneManagement()
			:m_ScopeName("")
		{
		}

		SceneManagement::SceneManagement(const std::string& scope)
			:m_ScopeName(scope)
		{
		}

		SceneManagement::~SceneManagement()
		{
		}

		Core::Ref<SceneManagement> SceneManagement::Copy(Core::Ref<SceneManagement> other, const std::string& newScopeName)
		{
			Core::Ref<SceneManagement> newScene = Core::CreateRef<SceneManagement>(newScopeName);

			auto& srcSceneRegistry = other->m_Registry;
			auto& dstSceneRegistry = newScene->m_Registry;
			std::unordered_map<Core::EngineUUID, entt::entity> enttMap;

			// Create entities in new scene
			auto idView = srcSceneRegistry.view<Components::IDComponent>();
			for (auto e : idView)
			{
				Core::EngineUUID uuid = srcSceneRegistry.get<Components::IDComponent>(e).ID;
				const std::string& name = srcSceneRegistry.get<Components::TagComponent>(e).Tag;
				Entity newEntity = newScene->CreateEntity(uuid, name);
				enttMap[uuid] = (entt::entity)newEntity;
			}

			// Copy components (except IDComponent and TagComponent)
			CopyComponent(Components::AllComponents{}, dstSceneRegistry, srcSceneRegistry, enttMap);
			
			return newScene;
		}

		Entity SceneManagement::CreateEntity()
		{
			return CreateEntity(Core::EngineUUID(), "entity");
		}

		Entity SceneManagement::CreateEntity(const std::string& name)
		{
			return CreateEntity(Core::EngineUUID(), name);
		}

		Entity SceneManagement::CreateEntity(Core::EngineUUID uuid, const std::string& name)
		{
			auto tagName = name.empty() ? "Entity" : name;
			int counter = 1;

			// Keep appending an incrementing number until a unique name is found
			while (m_StrToEntityMap.find(tagName) != m_StrToEntityMap.end()) {
				tagName = tagName + std::to_string(counter);
				counter++;
			}

			Entity entity = { m_Registry.create(), this };
			entity.AddComponent<Components::IDComponent>(uuid);
			entity.AddComponent<Components::TransformComponent>();
			auto& tag = entity.AddComponent<Components::TagComponent>();
			tag.Tag = tagName;

			m_UUIDToEntityMap[uuid] = entity;
			m_StrToEntityMap[tagName] = entity;

			return entity;
		}

		void SceneManagement::DestroyEntity(Entity entity)
		{
			m_UUIDToEntityMap.erase(entity.GetUUID());
			m_StrToEntityMap.erase(entity.GetName());
			m_Registry.destroy(entity);
		}

		Entity SceneManagement::Duplicate(Entity entity)
		{
			std::string name = entity.GetName();
			Entity newEntity = CreateEntity(name);
			CopyComponentIfExists(Components::AllComponents{}, newEntity, entity);
			return newEntity;
		}

		Entity SceneManagement::FindEntityByName(const std::string& name)
		{
			if (m_StrToEntityMap.find(name) != m_StrToEntityMap.end())
				return { m_StrToEntityMap.at(name), this };

			return {};
		}

		Entity SceneManagement::FindEntityByUUID(Core::EngineUUID uuid)
		{
			if (m_UUIDToEntityMap.find(uuid) != m_UUIDToEntityMap.end())
				return { m_UUIDToEntityMap.at(uuid), this };

			return {};
		}

		template<typename T>
		void SceneManagement::OnComponentAdded(Entity entity, T& component)
		{
			static_assert(sizeof(T) == 0);
		}

		template<>
		void SceneManagement::OnComponentAdded(Entity entity, Components::IDComponent& component)
		{
		}

		template<>
		void SceneManagement::OnComponentAdded(Entity entity, Components::TagComponent& component)
		{
		}

		template<>
		void SceneManagement::OnComponentAdded(Entity entity, Components::TransformComponent& component)
		{
		}

		template<>
		void SceneManagement::OnComponentAdded(Entity entity, Components::TextComponent& component)
		{
		}

		template<>
		void SceneManagement::OnComponentAdded(Entity entity, Components::SpriteRendererComponent& component)
		{
		}
	}
}