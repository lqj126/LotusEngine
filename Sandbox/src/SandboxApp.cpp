#include <Lotus.h>
#include "Lotus/Core/EntryPoint.h"
#include "Sandbox2D.h"
#include "Sandbox3D.h"


class Sandbox : public Lotus::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox3D());
	}

	~Sandbox()
	{

	}

};

Lotus::Application* Lotus::CreateApplication()
{
	return new Sandbox();
}