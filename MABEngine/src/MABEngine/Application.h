#pragma once

#include "Core.h"
#include "MABEngine/Events/Event.h"

namespace MABEngine {
	class MABENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	};

	// To be defined in Projects that want to use MABEngine
	Application* CreateApplication(int argc, char** argv);
}