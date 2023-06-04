#pragma once

#include "Lotus/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lotus {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
		virtual GLFWwindow* GetGLFWwindow() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}