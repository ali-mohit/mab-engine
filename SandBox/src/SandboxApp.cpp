#include "mabengine_pch.h"
#include "MABEngine/Layers/ImGui/ImGuiLayer.h"
#include <MABEngine.h>

#include <imgui.h>


class ExampleLayer : public MABEngine::Layers::Layer {
public:
	ExampleLayer() 
		: Layer("Example") 
	{}

	void OnUpdate() override {
		
	}

	void OnImGuiRender() override {
		ImGui::Begin("Hello world");
		ImGui::Text("This is my first sentence.");
		ImGui::End();
	}

	void OnEvent(MABEngine::Events::Event& event) override {
		
	}
};

class SandBoxApp : public MABEngine::Application {
public:
	SandBoxApp() {
		PushLayer(new ExampleLayer());
	}
	~SandBoxApp() {

	}
};

MABEngine::Application* MABEngine::CreateApplication(int argc, char** argv) {
	return new SandBoxApp();
}
