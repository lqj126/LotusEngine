#include "ltpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Lotus {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, void* data)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    LT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height, data);
		}

		LT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, const uint32_t RendererID)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    LT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height, RendererID);
		}

		LT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    LT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(path);
		}

		LT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::CreateFlatColor(const glm::vec4& color)
	{
		uint32_t flatColorData =
			(uint32_t)(color.a * 255) << 24 |
			(uint32_t)(color.b * 255) << 16 |
			(uint32_t)(color.g * 255) << 8 |
			(uint32_t)(color.r * 255);
		return Texture2D::Create(1, 1, &flatColorData);
	}
}