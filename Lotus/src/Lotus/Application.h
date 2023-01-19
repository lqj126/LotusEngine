#pragma once

#include "Core.h"

#include "Window.h"
#include "Lotus/LayerStack.h"
#include "Lotus/Events/Event.h"
#include "Lotus/Events/ApplicationEvent.h"


namespace Lotus{

	class LOTUS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnwindowClose(WindowCloseEvent& e);


		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};
	//To be defined in CLIENT
	Application* CreateApplication();
}

