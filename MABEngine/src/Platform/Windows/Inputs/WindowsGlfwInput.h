#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Inputs/Input.h"
#include "MABEngine/Inputs/MouseButtonCodes.h"
#include "MABEngine/Inputs/KeyboardCodes.h"

namespace MABEngine {
	namespace Inputs {
		class MABENGINE_API WindowsGlfwInput : public Input {
		protected:
			virtual bool IsKeyPressedImp(MABKeyboardCode keyCode) override;
			virtual bool IsKeyRepeatImp(MABKeyboardCode keyCode) override;

			virtual bool IsMouseButtonPressedImp(MABMouseButton buttonCode) override;
			virtual std::pair<double, double> GetMousePosImp() override;
			virtual double GetMousePosXImp() override;
			virtual double GetMousePosYImp() override;
		};
	}
}