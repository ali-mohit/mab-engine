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
		
		uint32_t w = GetWindow().GetWidth();
		uint32_t h = GetWindow().GetHeight();

		PushLayer(new ExampleLayer(w, h));
		//PushLayer(new StdViewPort(w, h));
	}
	~SandBoxApp() {

	}
};

MABEngine::Application* MABEngine::CreateApplication(int argc, char** argv) {
	return new SandBoxApp();
}
