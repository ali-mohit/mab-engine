#pragma once

#include "MABEngine/Events/Event.h"
#include "MABEngine/Inputs/KeyboardCodes.h"

namespace MABEngine {

	namespace Events {
		
		class MABENGINE_API KeyEvent : public Event {
		public:
			inline Inputs::MABKeyboardCode GetKeyCode() const { return m_KeyCode; }

			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		protected:
			KeyEvent(Inputs::MABKeyboardCode keyCode)
				: m_KeyCode(keyCode) {}

			Inputs::MABKeyboardCode m_KeyCode;
		};

		
		class MABENGINE_API	KeyPressedEvent : public KeyEvent {
		public:
			KeyPressedEvent(Inputs::MABKeyboardCode keyCode, int repeatCount)
				: KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

			inline int GetRepeatCount() const { return m_RepeatCount; }

			std::string ToString() const override {
				std::stringstream ss;

				ss << "KeyPressedEvent: " << static_cast<int>(m_KeyCode) << " (" << m_RepeatCount << " repeats)";

				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyPressed)
		private:
			int m_RepeatCount;
		};


		class MABENGINE_API KeyReleasedEvent : public KeyEvent {
		public:
			KeyReleasedEvent(Inputs::MABKeyboardCode keycode)
				: KeyEvent(keycode) {}

			std::string ToString() const override
			{
				std::stringstream ss;

				ss << "KeyReleasedEvent: " << static_cast<int>(m_KeyCode);
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyReleased)
		};
	}
}