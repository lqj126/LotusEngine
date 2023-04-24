#pragma once

#include "RendererAPI.h"

namespace Lotus {

	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(uint32_t elementCount)
		{
			s_RendererAPI->DrawIndexed(elementCount);
		}

		inline static void Draw(int fisrt, uint32_t elementCount)
		{
			s_RendererAPI->Draw(fisrt, elementCount);
		}

		inline static void DrawSphere()
		{
			s_RendererAPI->DrawSphere();
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}
