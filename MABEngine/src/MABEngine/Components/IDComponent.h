#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Core/EngineUUID.h"


namespace MABEngine {
	namespace Components {

		struct MABENGINE_API IDComponent
		{
			Core::EngineUUID ID;

			IDComponent() = default;
			IDComponent(const IDComponent&) = default;
		};

	}
}
