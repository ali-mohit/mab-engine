#pragma once

#include "MABEngine/Core/EngineTime.h"

namespace MABEngine {
	namespace Core {

		class GlfwTime : public EngineTime {
		public:
			virtual double GetTime() override;
		};

	}
}
