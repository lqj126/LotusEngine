#include <Lotus.h>

#include "imgui/imgui.h"

class ExampleLayer : public Lotus::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Lotus::Input::IsKeyPressed(LT_KEY_TAB))
			LT_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Lotus::Event& event) override
	{
		if (event.GetEventType() == Lotus::EventType::KeyPressed)
		{
			Lotus::KeyPressedEvent& e = (Lotus::KeyPressedEvent&)event;
			if (e.GetKeyCode() == LT_KEY_TAB)
				LT_TRACE("Tab key is pressed (event)!");
			LT_TRACE("{0}", (char)e.GetKeyCode());
		}
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