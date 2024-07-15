#include <mabengine_pch.h>
#include <MABEngine.h>
#include <MABEngine/Core/EntryPoint.h>
#include <MABEngine/Layers/ImGui/ImGuiLayer.h>
#include <imgui.h>

#include "SandBox3DLayer.h"
#include "SandBox2DLayer.h"
#include "SimpleGame/GameLayer.h"
#include "StdViewport.h"


class SandBoxApp : public MABEngine::Core::Application {
public:
	SandBoxApp() {
		
		uint32_t w = GetWindow().GetWidth();
		uint32_t h = GetWindow().GetHeight();

		//PushLayer(new SandBox3DLayer(w, h));
		//PushLayer(new SandBox2DLayer(w, h));
		PushLayer(new SimpleGame::GameLayer(w, h));
	}
	~SandBoxApp() {

	}
};

MABEngine::Core::Application* MABEngine::Core::CreateApplication(int argc, char** argv) {
	return new SandBoxApp();
}
