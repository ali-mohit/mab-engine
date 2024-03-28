#include "mabengine_pch.h"
#include <MABEngine.h>

class ExampleLayer : public MABEngine::Layers::Layer {
public:
	ExampleLayer() 
		: Layer("Example") 
	{}

	void OnUpdate() override {
		MAB_INFO("EXAMLE LAYER::Update()");
	}

	void OnEvent(MABEngine::Events::Event& event) override {
		MAB_TRACE("{0}", event);
	}
};

class SandBoxApp : public MABEngine::Application {
public:
	SandBoxApp() {
		PushLayer(new ExampleLayer());
		PushOverLayer(new MABEngine::Layers::ImGuiLayer());
	}
	~SandBoxApp() {

	}
};


MABEngine::Application* MABEngine::CreateApplication(int argc, char** argv) {
	return new SandBoxApp();
}
