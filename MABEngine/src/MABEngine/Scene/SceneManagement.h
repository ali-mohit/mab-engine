#pragma once

#include "MABEngine/Core/Base.h"

#include "entt.hpp"

namespace MABEngine {

	namespace Scene {

		class MABENGINE_API SceneManagement {
		public:
			SceneManagement();
			~SceneManagement();
		private:
			entt::registry m_Registry;
		};

	}
}