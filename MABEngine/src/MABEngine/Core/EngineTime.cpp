#include "mabengine_pch.h"

#include "Platform/Windows/Core/WindowsGlfwTime.h"

#include "MABEngine/Core/EngineTime.h"


namespace MABEngine {
	namespace Core {

		EngineTime* EngineTime::Create() {
			return new GlfwTime();
		}

	}
}