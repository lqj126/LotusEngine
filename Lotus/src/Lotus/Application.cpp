#include "Application.h"


#include "Lotus/Events/ApplicationEvent.h"
#include "Lotus/log.h"

namespace Lotus {
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		LT_TRACE(e);

		while (true);
	}
}