#pragma once

#include "MABEngine/Core/Window.h"
#include "MABEngine/Renderer/GraphicContext.h"

struct GLFWwindow;

namespace MABEngine {
	namespace Core {
		class MABENGINE_API WindowsGlfwWindow : public Core::Window
		{
		public:
			WindowsGlfwWindow(const Core::WindowProps& props);
		
			virtual ~WindowsGlfwWindow();

			void OnUpdate() override;

			inline unsigned int GetWidth() const override { return m_Data.Width; }
			inline unsigned int GetHeight() const override { return m_Data.Height; }

			// Window Attributes
			inline void SetEventCallBack(const EventCallBackFn& callback) override { m_Data.EventCallBack = callback; }
			void SetVSync(bool enabaled) override;
			bool IsVSync() const override;

			inline virtual void* GetNativeWindow() const override { return m_Window; }
		private:
			virtual void Init(const WindowProps& props);
			virtual void Shutdown();
		private:
			GLFWwindow* m_Window;
			Renderer::GraphicContext* m_GraphicContext;

			struct WindowData {
				std::string Title;
				unsigned int Width;
				unsigned int Height;

				bool VSync;
				EventCallBackFn EventCallBack;
			};

			WindowData m_Data;
		};
	}
}


