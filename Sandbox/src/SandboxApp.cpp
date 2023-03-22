#include <Lotus.h>
#include "Sandbox2D.h"
#include "Lotus/Core/EntryPoint.h"


class Sandbox : public Lotus::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}

};

Lotus::Application* Lotus::CreateApplication()
{
	return new Sandbox();
}