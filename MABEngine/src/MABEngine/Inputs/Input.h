#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Inputs/KeyboardCodes.h"
#include "MABEngine/Inputs/MouseButtonCodes.h"


namespace MABEngine {
	
	namespace Inputs {

		class MABENGINE_API Input {
		public:
			
			static bool IsKeyPressed(MABKeyboardCode keyCode);
			static bool IsKeyRepeat(MABKeyboardCode keyCode);

			static bool IsMouseButtonPressed(MABMouseButton buttonCode);
			static std::pair<double, double> GetMousePos();
			static void SetMousePos(double x, double y);
			static double GetMousePosX();
			static double GetMousePosY();
		
			static void HideMouseCursor();
			static void ShowMouseCursor();
		};

	}
}
