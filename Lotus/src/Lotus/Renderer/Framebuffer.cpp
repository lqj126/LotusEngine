#include "ltpch.h"
#include "Framebuffer.h"

#include "Lotus/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Lotus {

	Framebuffer* Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    LT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLFramebuffer(spec);
		}

		LT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}