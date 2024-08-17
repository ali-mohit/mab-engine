#include "mabengine_pch.h"
#include "MABEngine/Scene/Entity.h"

namespace MABEngine {
	namespace Scene {
		Entity::Entity(entt::entity handle, SceneManagement* scene)
			:m_EntityHandle(handle), m_Repo(scene) {}


	}
}