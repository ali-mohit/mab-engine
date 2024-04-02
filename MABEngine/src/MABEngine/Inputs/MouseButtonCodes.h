#pragma once

#include "MABEngine/Inputs/MouseButtonCodesDefine.h"

namespace MABEngine {
	namespace Inputs {
		static const std::string mab_mouse_uknown = "MAB_MOUSE_UKNOWN";
		static const std::string mab_mouse_button_1 = "Mab_Mouse_Button_1";
		static const std::string mab_mouse_button_2 = "Mab_Mouse_Button_2";
		static const std::string mab_mouse_button_3 = "Mab_Mouse_Button_3";
		static const std::string mab_mouse_button_4 = "Mab_Mouse_Button_4";
		static const std::string mab_mouse_button_5 = "Mab_Mouse_Button_5";
		static const std::string mab_mouse_button_6 = "Mab_Mouse_Button_6";
		static const std::string mab_mouse_button_7 = "Mab_Mouse_Button_7";
		static const std::string mab_mouse_button_8 = "Mab_Mouse_Button_8";
		static const std::string mab_mouse_button_last = "Mab_Mouse_Button_Last";
		static const std::string mab_mouse_button_left = "Mab_Mouse_Button_Left";
		static const std::string mab_mouse_button_right = "Mab_Mouse_Button_Right";
		static const std::string mab_mouse_button_middle = "Mab_Mouse_Button_Middle";

		enum MABMouseButton {
			Mab_Mouse_Uknown = MAB_MOUSE_UKNOWN,
			Mab_Mouse_Button_1 = MAB_MOUSE_BUTTON_1,
			Mab_Mouse_Button_2 = MAB_MOUSE_BUTTON_2,
			Mab_Mouse_Button_3 = MAB_MOUSE_BUTTON_3,
			Mab_Mouse_Button_4 = MAB_MOUSE_BUTTON_4,
			Mab_Mouse_Button_5 = MAB_MOUSE_BUTTON_5,
			Mab_Mouse_Button_6 = MAB_MOUSE_BUTTON_6,
			Mab_Mouse_Button_7 = MAB_MOUSE_BUTTON_7,
			Mab_Mouse_Button_8 = MAB_MOUSE_BUTTON_8,
			Mab_Mouse_Button_Last = MAB_MOUSE_BUTTON_LAST,
			Mab_Mouse_Button_Left = MAB_MOUSE_BUTTON_LEFT,
			Mab_Mouse_Button_Right = MAB_MOUSE_BUTTON_RIGHT,
			Mab_Mouse_Button_Middle = MAB_MOUSE_BUTTON_MIDDLE,
		};

		static const std::unordered_map<std::string, MABMouseButton> stringToMABMouseButtonsMap = {
			{"Mab_Mouse_Button_1", Mab_Mouse_Button_1},
			{"Mab_Mouse_Button_2", Mab_Mouse_Button_2},
			{"Mab_Mouse_Button_3", Mab_Mouse_Button_3},
			{"Mab_Mouse_Button_4", Mab_Mouse_Button_4},
			{"Mab_Mouse_Button_5", Mab_Mouse_Button_5},
			{"Mab_Mouse_Button_6", Mab_Mouse_Button_6},
			{"Mab_Mouse_Button_7", Mab_Mouse_Button_7},
			{"Mab_Mouse_Button_8", Mab_Mouse_Button_8},
			{"Mab_Mouse_Button_Last", Mab_Mouse_Button_Last},
			{"Mab_Mouse_Button_Left", Mab_Mouse_Button_Left},
			{"Mab_Mouse_Button_Right", Mab_Mouse_Button_Right},
			{"Mab_Mouse_Button_Middle", Mab_Mouse_Button_Middle},
		};

		inline std::string MABMouseButtonsToString(const MABMouseButton& buttonCode) {
			switch (buttonCode) {
			case Mab_Mouse_Button_1: return mab_mouse_button_1;
			case Mab_Mouse_Button_2: return mab_mouse_button_2;
			case Mab_Mouse_Button_3: return mab_mouse_button_3;
			case Mab_Mouse_Button_4: return mab_mouse_button_4;
			case Mab_Mouse_Button_5: return mab_mouse_button_5;
			case Mab_Mouse_Button_6: return mab_mouse_button_6;
			case Mab_Mouse_Button_7: return mab_mouse_button_7;
			case Mab_Mouse_Button_8: return mab_mouse_button_8;
			default:
				return mab_mouse_uknown;
			}
		}

		inline MABMouseButton StringToMABMouseButtons(const std::string& mouseButtonStr) {
			auto it = stringToMABMouseButtonsMap.find(mouseButtonStr);
			if (it != stringToMABMouseButtonsMap.end()) return it->second;
			else return Mab_Mouse_Uknown;
		}
	}
}
