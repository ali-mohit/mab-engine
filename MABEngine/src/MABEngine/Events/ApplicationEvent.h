#pragma once

#include "MABEngine/Events/Event.h"

namespace MABEngine {

	namespace Events {
		
		class MABENGINE_API WindowResizeEvent : public Event {
		public:
			WindowResizeEvent(unsigned int width, unsigned int height)
				: m_Width(width), m_Height(height) { }

			inline unsigned int GetWidth() const { return m_Width; }
			inline unsigned int GetHeight() const { return m_Height; }

			std::string ToString() const override {
				std::stringstream ss;
				ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
				return ss.str();
			}

			EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		private:
			unsigned int m_Width;
			unsigned int m_Height;
		};

		class MABENGINE_API WindowCloseEvent : public Event {
		public:
			WindowCloseEvent() {}

			EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};

		// WindowFocus, WindowLossFocus, WindowMoved,
		class MABENGINE_API WindowFocusEvent : public Event {
		public:
			WindowFocusEvent() {}

			EVENT_CLASS_TYPE(WindowFocus)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};

		class MABENGINE_API WindowLossFocusEvent : public Event {
		public:
			WindowLossFocusEvent() {}

			EVENT_CLASS_TYPE(WindowLossFocus)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};

		class MABENGINE_API WindowMovedEvent : public Event {
		public:
			WindowMovedEvent() {}

			EVENT_CLASS_TYPE(WindowMoved)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};


		class MABENGINE_API AppTickEvent : public Event {
		public:
			AppTickEvent() {}

			EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};

		class MABENGINE_API AppUpdateEvent : public Event {
		public:
			AppUpdateEvent() {}

			EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};

		class MABENGINE_API AppRenderEvent : public Event {
		public:
			AppRenderEvent() {}

			EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};
	}
}