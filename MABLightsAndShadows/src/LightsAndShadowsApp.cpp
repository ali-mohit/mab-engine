#include <mabengine_pch.h>
#include <MABEngine.h>
#include <MABEngine/Core/EntryPoint.h>
#include <MABEngine/Layers/ImGui/ImGuiLayer.h>
#include <imgui.h>

#include "LightsAndShadows/Layers/MainLayer.h"

namespace LightsAndShadows{

	class LightsAndShadowsApp : public MABEngine::Core::Application {
	public:
		LightsAndShadowsApp() : Application() {

			uint32_t w = GetWindow().GetWidth();
			uint32_t h = GetWindow().GetHeight();

			PushLayer(new Layers::MainLayer(w, h));
		}
		LightsAndShadowsApp(const MABEngine::Core::ApplicationProps props): Application(props) {

			uint32_t w = props.DefaultWidth;
			uint32_t h = props.DefaultHeight;

			PushLayer(new Layers::MainLayer(w, h));
		}
		~LightsAndShadowsApp() {

		}
	};
}

MABEngine::Core::Application* MABEngine::Core::CreateApplication(int argc, char** argv) {
	MABEngine::Core::ApplicationProps appProps("MAB Lights And Shadows", 1280, 720);
	return new LightsAndShadows::LightsAndShadowsApp(appProps);
}