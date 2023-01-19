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

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnwindowClose));

		LT_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running);
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}
	bool Application::OnwindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}