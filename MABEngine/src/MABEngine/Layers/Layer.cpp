#include "mabengine_pch.h"
#include "Layer.h"

namespace MABEngine {
	namespace Layers {

		Layer::Layer(const std::string& name)
			:m_DebugName(name)
		{
		}

		Layer::~Layer()
		{
		}
	}
}