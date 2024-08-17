#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Core/EngineUUID.h"
#include "MABEngine/Scene/Entity.h"
#include "MABEngine/Components/ComponentGroup.h"

#include <entt.hpp>
#include <unordered_map>

namespace MABEngine {
	namespace Scene {

		template<typename... Component>
		inline static void CopyComponent(
			entt::registry& dst, entt::registry& src,
			const std::unordered_map<Core::EngineUUID, entt::entity>& enttMap
		)
		{
			([&]()
				{
					auto view = src.view<Component>();
					for (auto srcEntity : view)
					{
						entt::entity dstEntity = enttMap.at(src.get<Components::IDComponent>(srcEntity).ID);

						auto& srcComponent = src.get<Component>(srcEntity);
						dst.emplace_or_replace<Component>(dstEntity, srcComponent);
					}
				}(), ...);
		}

		template<typename... Component>
		inline static void CopyComponent(
			Components::ComponentGroup<Component...>,
			entt::registry& dst,
			entt::registry& src,
			const std::unordered_map<Core::EngineUUID, entt::entity>& enttMap)
		{
			CopyComponent<Component...>(dst, src, enttMap);
		}

		template<typename... Component>
		inline static void CopyComponentIfExists(Entity dst, Entity src)
		{
			([&]()
				{
					if (src.HasComponent<Component>())
						dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
				}(), ...);
		}

		template<typename... Component>
		inline static void CopyComponentIfExists(Components::ComponentGroup<Component...>, Entity dst, Entity src)
		{
			CopyComponentIfExists<Component...>(dst, src);
		}
	}
}