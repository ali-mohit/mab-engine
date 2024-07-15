#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Core/EngineUUID.h"

#include <string>

namespace MABEngine {
	namespace Core {
		class MABENGINE_API EngineObject {
		public:
			const std::string& ID() const { return m_ID; }
			std::string ID() { return m_ID; }
		private:
			std::string m_ID = generateUUID();
		};
	}
}
