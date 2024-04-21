#include "mabengine_pch.h"
#include "BufferLayout.h"

namespace MABEngine {
	namespace Renderer {

		void BufferLayout::CalculateOffsetAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& item : m_BufferElements) {
				item.Offset = offset;
				offset += item.Size;
				m_Stride += item.Size;
			}
		}

	}
}

