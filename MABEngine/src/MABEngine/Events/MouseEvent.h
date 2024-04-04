#pragma once

#include "MABEngine/Events/Event.h"
#include "MABEngine/Inputs/MouseButtonCodes.h"

namespace MABEngine {
	namespace Events {

		class MABENGINE_API MouseMovedEvent : public Event {
		public:
			MouseMovedEvent(float x, float y)
				: m_MouseX(x), m_MouseY(y) {}
			
			inline float GetX() const { return m_MouseX; }
			inline float GetY() const { return m_MouseY; }

			std::string ToString() const override {
				std::stringstream ss;
				ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		private:
			float m_MouseX;
			float m_MouseY;
		};

		class MABENGINE_API MouseScrolledEvent : public Event {
		public:
			MouseScrolledEvent(double xOffset, double yOffset) 
				: m_XOffset(xOffset), m_YOffset(yOffset) {}

			inline double GetXOffSet() const { return m_XOffset; }
			inline double GetYOffSet() const { return m_YOffset; }

			std::string ToString() const override {
				std::stringstream ss;
				ss << "MouseScrolledEvent: " << GetXOffSet() << ", " << GetYOffSet();
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		private: 
			double m_XOffset;
			double m_YOffset;
		};


		class MABENGINE_API MouseButtonEvent : public Event {
		public:
			inline Inputs::MABMouseButton GetMouseButton() const { return m_Button; }

			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		protected:
			MouseButtonEvent(Inputs::MABMouseButton button):
				m_Button(button) {}

			Inputs::MABMouseButton m_Button;
		};

		class MABENGINE_API MouseButtonPressedEvent : public MouseButtonEvent {
		public:
			MouseButtonPressedEvent(Inputs::MABMouseButton button)
				: MouseButtonEvent(button) {}

			std::string ToString() const override {
				std::stringstream ss;
				ss << "MouseButtonPressedEvent: " << static_cast<int>(m_Button);
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseButtonPressed)
		};

		class MABENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent {
		public:
			MouseButtonReleasedEvent(Inputs::MABMouseButton button)
				: MouseButtonEvent(button) {}
			
			std::string ToString() const override {
				std::stringstream ss;

				ss << "MouseButtonReleasedEvent: " << static_cast<int>(m_Button);
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseButtonReleased)
		};

	}
}