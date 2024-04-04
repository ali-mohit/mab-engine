#pragma once

#include "MABEngine/Core.h"
#include "MABEngine/Inputs/KeyboardCodes.h"
#include "MABEngine/Inputs/MouseButtonCodes.h"


namespace MABEngine {
	
	namespace Inputs {

		class MABENGINE_API Input {
		public:
			inline static bool IsKeyPressed(MABKeyboardCode keyCode) { return s_Instance->IsKeyPressedImp(keyCode); }
			inline static bool IsKeyRepeat(MABKeyboardCode keyCode) { return s_Instance->IsKeyRepeatImp(keyCode); }

			inline static bool IsMouseButtonPressed(MABMouseButton buttonCode) { return s_Instance->IsMouseButtonPressedImp(buttonCode); }
			inline static std::pair<double, double> GetMousePos() { return s_Instance->GetMousePosImp(); }
			inline static double GetMousePosX() { return s_Instance->GetMousePosXImp(); }
			inline static double GetMousePosY() { return s_Instance->GetMousePosYImp(); }
		protected:
			virtual bool IsKeyPressedImp(MABKeyboardCode keyCode) = 0;
			virtual bool IsKeyRepeatImp(MABKeyboardCode keyCode) = 0;

			virtual bool IsMouseButtonPressedImp(MABMouseButton buttonCode) = 0;
			virtual std::pair<double, double> GetMousePosImp() = 0;
			virtual double GetMousePosXImp() = 0;
			virtual double GetMousePosYImp() = 0;
		private:
			static Input* s_Instance;
		};

	}
}
