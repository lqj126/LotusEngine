#include "ltpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Lotus {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
<<<<<<< HEAD
<<<<<<< HEAD
			case RendererAPI::API::None:    LT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
=======
		case RendererAPI::None:    LT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLVertexArray();
>>>>>>> 2b2bd744763595dbc2248baf9251b6cb29fc7e8e
=======
		case RendererAPI::None:    LT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLVertexArray();
>>>>>>> 2b2bd744763595dbc2248baf9251b6cb29fc7e8e
		}

		LT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}