#pragma once
struct GLFWwindow;
namespace Lotus {

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual GLFWwindow* GetGLFWwindow() = 0;
	};

}