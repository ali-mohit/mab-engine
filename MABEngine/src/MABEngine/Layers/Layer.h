#pragma once

#include "MABEngine/Core.h"
#include "MABEngine/Core/TimeStep.h"

#include "MABEngine/Events/Event.h"


namespace MABEngine {
	namespace Layers {

		class MABENGINE_API Layer
		{
		public:
			Layer(const std::string& name = "Layer");
			virtual ~Layer();

			virtual void OnAttach() {}
			virtual void OnDetach() {}
			virtual void OnUpdate(MABEngine::Core::EngineTimeStep ts) {}
			virtual void OnImGuiRender() {}
			virtual void OnEvent(Events::Event& event) {}

			inline const std::string& GetName() const { return m_DebugName; }
		protected:
			std::string m_DebugName;
		};
	}
}


