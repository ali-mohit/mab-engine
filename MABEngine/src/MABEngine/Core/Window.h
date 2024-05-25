#pragma once

#include "mabengine_pch.h"

#include "MABEngine/Core/Base.h"
#include "MABEngine/Events/Event.h"


namespace MABEngine {
	namespace Core {

		struct WindowProps {
			std::string Title;
			unsigned int Width;
			unsigned int Height;

			WindowProps(const std::string& title = "MAB Engine",
				unsigned int width = 1280,
				unsigned int height = 720)
				: Title(title), Width(width), Height(height)
			{
			}
		};

		// Public Interface for all desktop platforms
		class MABENGINE_API Window {
		public:
			using EventCallBackFn = std::function<void(Events::Event&)>;

			virtual ~Window() {}
			virtual void OnUpdate() = 0;

			virtual unsigned int GetWidth() const = 0;
			virtual unsigned int GetHeight() const = 0;

			virtual void SetEventCallBack(const EventCallBackFn& callback) = 0;
			virtual void SetVSync(bool enabled) = 0;
			virtual bool IsVSync() const = 0;

			virtual void* GetNativeWindow() const = 0;

			static Window* Create(const WindowProps& props = WindowProps());
		};

	}
}