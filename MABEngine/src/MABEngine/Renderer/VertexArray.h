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

			virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
			virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

			virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBufferList() const = 0;
			virtual const std::vector<std::shared_ptr<IndexBuffer>>& GetIndexBufferList() const = 0;


			static VertexArray* Create();
		};

	}
}