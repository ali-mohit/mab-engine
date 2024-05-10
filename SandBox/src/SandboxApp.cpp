#include <mabengine_pch.h>
#include <MABEngine.h>
#include <MABEngine/EntryPoint.h>
#include <MABEngine/Layers/ImGui/ImGuiLayer.h>
#include <imgui.h>

#include "ExampleLayer.h"
#include "StdViewport.h"


class SandBoxApp : public MABEngine::Application {
public:
	SandBoxApp() {
		PushLayer(new ExampleLayer());
		PushLayer(new StdViewPort());
	}
	~SandBoxApp() {

	}
};

MABEngine::Application* MABEngine::CreateApplication(int argc, char** argv) {
	return new SandBoxApp();
}
