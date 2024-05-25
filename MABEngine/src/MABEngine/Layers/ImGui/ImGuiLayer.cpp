#include "mabengine_pch.h"
#include "MABEngine/Layers/ImGui/ImGuiLayer.h"

#include "imgui.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


#include "MABEngine/Core/Application.h"
#include "MABEngine/Events/Event.h"


namespace MABEngine {

    namespace Layers {
        ImGuiLayer::ImGuiLayer()
            : Layer("ImGuiLayer")
        {
        }

        ImGuiLayer::ImGuiLayer(std::string layerName)
            : Layer(layerName)
        {
        }

        ImGuiLayer::~ImGuiLayer()
        {
        }

        void ImGuiLayer::OnAttach()
        {
            //Setup ImGui Context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking 
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         //Enable Multi Viewports
            //io.ConfigViewportsNoAutoMerge = true;
            //io.ConfigViewportsNoTaskBarIcon = true;
    
            //Setup Dear ImGUI style
            ImGui::StyleColorsDark();
            //ImGui::StyleColorsClassic();
            
            ImGuiStyle& style = ImGui::GetStyle();
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                style.WindowRounding = 0.0f;
                style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            }

            Core::Application& app = Core::Application::Get();
            GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

            //Setup Platform/Renderer bindings
            if (!isImGuiGlfwInitialized) {
                ImGui_ImplGlfw_InitForOpenGL(window, true);
                ImGui_ImplOpenGL3_Init("#version 430");
                isImGuiGlfwInitialized = true;
            }
            
        }

        void ImGuiLayer::OnEvent(Events::Event& event)
        {
            if (m_BlockEvents) {
                ImGuiIO& io = ImGui::GetIO();
                event.Handled |= event.IsInCategory(Events::EventCategoryMouse) & io.WantCaptureMouse;
                event.Handled |= event.IsInCategory(Events::EventCategoryKeyboard) & io.WantCaptureKeyboard;
            }
        }

        void ImGuiLayer::OnDetach()
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
        void ImGuiLayer::Begin() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void ImGuiLayer::End() {
            ImGuiIO& io = ImGui::GetIO();
            Core::Application& app = Core::Application::Get();
            io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(),(float)app.GetWindow().GetHeight());

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                GLFWwindow* backupCurrentContext = glfwGetCurrentContext();

                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();

                glfwMakeContextCurrent(backupCurrentContext);
            }
        }

        void ImGuiLayer::OnImGuiRender() {
            
        }
    }

}