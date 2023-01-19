#include "ltpch.h"
#include "Application.h"

#include "Lotus/Events/ApplicationEvent.h"
#include "Lotus/log.h"
#include "GLFW/glfw3.h"

namespace Lotus {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running);
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}