#pragma once

#include "MABEngine/Window.h"

struct GLFWwindow;

namespace MABEngine {
	class MABENGINE_API WindowsGlfwWindow : public Window
	{
	public:
		WindowsGlfwWindow(const WindowProps& props);
		
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


