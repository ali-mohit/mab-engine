#pragma once
#include "MABEngine/Core/Base.h"

namespace MABEngine {

	namespace Renderer {

		struct MABENGINE_API FrameBufferSpecification {
			uint32_t Width = 0;
			uint32_t Height = 0;
			uint32_t SampleCount = 1;

			bool ActivateDepthBuffer = true;

			FrameBufferSpecification() {};
			FrameBufferSpecification(uint32_t width, uint32_t height, uint32_t sampleCount = 1, bool activateDepthBuffer = true)
				:Width(width), Height(height), SampleCount(sampleCount), ActivateDepthBuffer(activateDepthBuffer) {}
		};

	}
}