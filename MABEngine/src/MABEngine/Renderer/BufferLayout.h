#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/BufferElement.h"

namespace MABEngine {

	namespace Renderer {

		class MABENGINE_API BufferLayout
		{
		public:
			BufferLayout() {}

			BufferLayout(const std::initializer_list<BufferElement>& elements)
				: m_BufferElements(elements)
			{
				CalculateOffsetAndStride();
			}

			inline const std::vector<BufferElement>& GetElements() const { return m_BufferElements; }
			inline const uint32_t GetStride() const { return m_Stride; }

			std::vector<BufferElement>::iterator begin() { return m_BufferElements.begin(); }
			std::vector<BufferElement>::iterator end() { return m_BufferElements.end(); }

			std::vector<BufferElement>::const_iterator begin() const { return m_BufferElements.begin(); }
			std::vector<BufferElement>::const_iterator end() const { return m_BufferElements.end(); }
		private:
			void CalculateOffsetAndStride();
		private:
			std::vector<BufferElement> m_BufferElements;
			uint32_t m_Stride = 0;
		};

	}
}

