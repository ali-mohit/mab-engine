#pragma once
#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/FrameBufferSpecification.h"

namespace MABEngine {

	namespace Renderer {

		class MABENGINE_API FrameBuffer {
		public:
			virtual ~FrameBuffer() = default;

			virtual void Bind() = 0;
			virtual void UnBind() = 0;

			virtual void Resize(uint32_t width, uint32_t height) = 0;

			virtual uint32_t GetRendererID() = 0;
			virtual uint32_t GetColorAttachmentID() = 0;
			virtual uint32_t GetDepthAttachmentID() = 0;


			virtual uint32_t GetWidth() = 0;
			virtual uint32_t GetHeight() = 0;
			virtual uint32_t GetSampleCount() = 0;
			virtual const FrameBufferSpecification& GetSpecification() const = 0;

			static Core::Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
		};

	}
}
