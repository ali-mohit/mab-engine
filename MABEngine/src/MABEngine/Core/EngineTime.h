#pragma once

#include "MABEngine/Core.h"

namespace MABEngine {
	namespace Core {
		class MABENGINE_API EngineTime {
		public:
			virtual double GetTime() = 0;

			static EngineTime* Create();
		};
	}
}
