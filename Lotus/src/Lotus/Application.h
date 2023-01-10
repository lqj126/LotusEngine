#pragma once

#include "Core.h"

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

