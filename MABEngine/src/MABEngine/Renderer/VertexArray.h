#pragma once

#include <memory>

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/VertexBuffer.h"
#include "MABEngine/Renderer/IndexBuffer.h"

namespace MABEngine {

	namespace Renderer {

		class MABENGINE_API VertexArray {
		public:
			~VertexArray() {}

			virtual void Bind() const = 0;
			virtual void UnBind() const = 0;

			virtual void AddVertexBuffer(const Core::Ref<VertexBuffer>& vertexBuffer) = 0;
			virtual void SetIndexBuffer(const Core::Ref<IndexBuffer>& indexBuffer) = 0;

			virtual const std::vector<Core::Ref<VertexBuffer>>& GetVertexBufferList() const = 0;
			virtual const Core::Ref<IndexBuffer>& GetIndexBuffer() const = 0;


			static Core::Ref<VertexArray> Create();
		};

	}
}