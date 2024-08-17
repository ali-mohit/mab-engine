#pragma once

#include "MABEngine/Components/TransformComponent.h"
#include "MABEngine/Components/TextComponent.h"
#include "MABEngine/Components/SpriteRendererComponent.h"

namespace MABEngine {
	namespace Components {
		template<typename... Component>
		struct MABENGINE_API ComponentGroup
		{
		};

		using AllComponents = ComponentGroup<
			TransformComponent,
			TextComponent,
			SpriteRendererComponent
		>;
	}
}
