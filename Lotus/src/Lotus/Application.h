#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Lotus{

	class LOTUS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};
	//To be defined in CLIENT
	Application* CreateApplication();
}

