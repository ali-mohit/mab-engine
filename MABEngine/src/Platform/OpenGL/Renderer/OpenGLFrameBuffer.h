#pragma once
#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/FrameBufferSpecification.h"
#include "MABEngine/Renderer/FramBuffer.h"

namespace MABEngine {

	namespace Renderer {

		class MABENGINE_API OpenGLFrameBuffer : public FrameBuffer {
		public:
			OpenGLFrameBuffer(const FrameBufferSpecification& spec);
			~OpenGLFrameBuffer();

			virtual void Bind() override;
			virtual void UnBind() override;

			virtual void Resize(uint32_t width, uint32_t height) override;

			void RebuildFrameBuffer();

			virtual uint32_t GetRendererID() override { return m_RendererID; }
			virtual uint32_t GetColorAttachmentID() override { return m_ColorAttachmentID; };
			virtual uint32_t GetDepthAttachmentID() override { return m_DepthAttachmentID; };

			virtual uint32_t GetWidth() override { return m_Specification.Width; }
			virtual uint32_t GetHeight() override { return m_Specification.Height; }
			virtual uint32_t GetSampleCount() override { return m_Specification.SampleCount; }
			virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; };

		private:
			FrameBufferSpecification m_Specification;
			uint32_t m_RendererID = 0;
			uint32_t m_ColorAttachmentID = 0;
			uint32_t m_DepthAttachmentID = 0;
		};

	}
}