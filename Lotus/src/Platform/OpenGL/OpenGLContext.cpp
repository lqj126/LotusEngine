#include "ltpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Lotus {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		LT_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LT_CORE_ASSERT(status, "Failed to initialize Glad!");

		LT_CORE_INFO("OpenGL Info:");
		LT_CORE_INFO("  Vendor: {0}", fmt::ptr(glGetString(GL_VENDOR)));
		LT_CORE_INFO("  Renderer: {0}", fmt::ptr(glGetString(GL_RENDERER)));
		LT_CORE_INFO("  Version: {:p}", fmt::ptr(glGetString(GL_VERSION)));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}