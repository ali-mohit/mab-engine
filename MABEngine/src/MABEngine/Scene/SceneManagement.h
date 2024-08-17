#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Core/EngineUUID.h"

#include <entt.hpp>
#include <unordered_map>

namespace MABEngine {

	namespace Scene {

		class Entity;

		class MABENGINE_API SceneManagement {
		public:
			SceneManagement();
			SceneManagement(const std::string& scope);
			~SceneManagement();

			static Core::Ref<SceneManagement> Copy(Core::Ref<SceneManagement> other, const std::string& newScopeName = "");

			Entity CreateEntity();
			Entity CreateEntity(const std::string& name);
			Entity CreateEntity(Core::EngineUUID uuid, const std::string& name);

			void DestroyEntity(Entity entity);

			Entity Duplicate(Entity entity);

			Entity FindEntityByName(const std::string& name);
			Entity FindEntityByUUID(Core::EngineUUID uuid);

			template<typename... Components>
			auto GetAllEntitiesWith()
			{
				return m_Registry.view<Components...>();
			}

			const std::string& GetScopeName() const { return m_ScopeName; }
		private:
			template<typename T>
			void OnComponentAdded(Entity entity, T& component);

		private:
			std::string m_ScopeName = "";
			entt::registry m_Registry;

			std::unordered_map<Core::EngineUUID, entt::entity> m_UUIDToEntityMap;
			std::unordered_map<std::string, entt::entity> m_StrToEntityMap;

			friend class Entity;
		};
	}
}