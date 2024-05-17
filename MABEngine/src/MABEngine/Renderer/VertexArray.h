#pragma once

#include <memory>

#include "MABEngine/Core.h"
#include "MABEngine/Renderer/VertexBuffer.h"
#include "MABEngine/Renderer/IndexBuffer.h"

namespace MABEngine {

	namespace Renderer {

		class MABENGINE_API VertexArray {
		public:
			~VertexArray() {}

			virtual void Bind() const = 0;
			virtual void UnBind() const = 0;

			virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
			virtual void AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

			virtual const std::vector<Ref<VertexBuffer>>& GetVertexBufferList() const = 0;
			virtual const std::vector<Ref<IndexBuffer>>& GetIndexBufferList() const = 0;


			static Ref<VertexArray> Create();
		};

	}
}