#include <Lotus.h>

class Sandbox : public Lotus::Application
{
public:
	Sandbox()
	{

	}
	
	~Sandbox()
	{

	}

};

Lotus::Application* Lotus::CreateApplication()
{
	return new Sandbox();
}