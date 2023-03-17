#pragma once

#include <memory>
#include "Lotus/Renderer/Buffer.h"

namespace Lotus {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

<<<<<<< HEAD
<<<<<<< HEAD
}
=======
}
>>>>>>> 2b2bd744763595dbc2248baf9251b6cb29fc7e8e
=======
}
>>>>>>> 2b2bd744763595dbc2248baf9251b6cb29fc7e8e
