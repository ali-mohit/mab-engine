#include <mabengine_pch.h>
#include <MABEngine.h>
#include <MABEngine/Core/EntryPoint.h>
#include <MABEngine/Layers/ImGui/ImGuiLayer.h>
#include <imgui.h>

#include "SandBoxLayers/SandBox3DLayer.h"
#include "SandBoxLayers/SandBox2DLayer.h"
#include "SandBoxLayers/DockSpaceView.h"
#include "SimpleGame/GameLayer.h"

class SandBoxApp : public MABEngine::Core::Application {
public:
	SandBoxApp() {
		
		uint32_t w = GetWindow().GetWidth();
		uint32_t h = GetWindow().GetHeight();

		//PushLayer(new SimpleGame::GameLayer(w, h));
		//PushLayer(new SandBoxLayers::SandBox3DLayer(w, h));
		//PushLayer(new SandBoxLayers::SandBox2DLayer(w, h));
		PushLayer(new SandBoxLayers::DockSpaceView(w, h));
	}
	~SandBoxApp() {

	}
};

MABEngine::Core::Application* MABEngine::Core::CreateApplication(int argc, char** argv) {
	return new SandBoxApp();
}
