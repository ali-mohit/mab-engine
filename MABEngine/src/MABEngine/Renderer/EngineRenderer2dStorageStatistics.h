#pragma once

#include "MABEngine/Core/Base.h"

#if ENGINE2D_STATISTICS == 1
	#define INCREASE_NUMBER_OF_QUADS(stats, number) stats.QuadCounts += number 
	#define INCREASE_NUMBER_OF_CALLS(stats, number) stats.NumberOfDrawCalls += number 
#else
	#define INCREASE_NUMBER_OF_QUADS(stats, number) 
	#define INCREASE_NUMBER_OF_CALLS(stats, number) 
#endif

namespace MABEngine {

	namespace Renderer {
		struct EngineRenderer2dStorageStatistics {
			uint32_t NumberOfDrawCalls = 0;
			uint32_t QuadCounts = 0;

			uint32_t GetTotalVertexCount() { return QuadCounts * 4; }
			uint32_t GetTotalEdgetCount() { return QuadCounts * 6; }
		};
	}
}