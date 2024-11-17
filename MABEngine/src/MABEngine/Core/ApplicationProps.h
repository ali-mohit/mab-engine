#pragma once
#include "mabengine_pch.h"
#include "MABEngine/Core/Base.h"

#include <string>

namespace MABEngine {
	namespace Core {
		struct MABENGINE_API ApplicationProps {
			std::string Title;
			uint32_t	DefaultWidth;
			uint32_t	DefaultHeight;
			uint32_t	DefaultSampling = 4;
			
			ApplicationProps() 
				:Title("MAB Engine"), DefaultWidth(1280), DefaultHeight(720) { }

			ApplicationProps(std::string title, uint32_t width, uint32_t height, uint32_t sampling)
				:Title(title), DefaultWidth(width), DefaultHeight(height), DefaultSampling(sampling) { }
		};
	}
}
