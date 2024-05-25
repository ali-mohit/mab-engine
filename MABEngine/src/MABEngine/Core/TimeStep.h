#pragma once

#include "MABEngine/Core/Base.h"

namespace MABEngine {
	namespace Core {
		
		class MABENGINE_API EngineTimeStep {
		public:
			EngineTimeStep(float time = 0.0f)
				:m_Time(time)
			{}

			operator float() { return m_Time; }

			float GetSecond() const { return m_Time; }
			float GetMillisecond() const { return m_Time * 1000.0f; }

		private:
			float m_Time;
		};

	}
}
