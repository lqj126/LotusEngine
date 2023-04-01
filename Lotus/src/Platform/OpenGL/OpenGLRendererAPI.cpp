#include "ltpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Lotus {

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(uint32_t elementCount)
	{
		glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::Draw(int first, uint32_t elementCount)
	{
		glDrawArrays(GL_TRIANGLES, first, elementCount);
	}

}
