#include <Lotus.h>

class ExampleLayer : public Lotus::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		LT_INFO("ExampleLayer::OnUpdate");
	}

	void OnEvent(Lotus::Event& event) override
	{
		LT_TRACE("{0}", event);
	}

};

class Sandbox : public Lotus::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	
	~Sandbox()
	{

	}

};

Lotus::Application* Lotus::CreateApplication()
{
	return new Sandbox();
}