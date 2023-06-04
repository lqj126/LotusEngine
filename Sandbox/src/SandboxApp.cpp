#include <Lotus.h>
#include "Lotus/Core/EntryPoint.h"
#include "Sandbox2D.h"
#include "Sandbox3D.h"
#include "SandboxPBR.h"
#include "SandboxPBRModel.h"
#include "SandboxManager.h"

class Sandbox : public Lotus::Application
{
public:
	Sandbox()
	{
		PushLayer(new Lotus::Sandbox3D());
	}

	~Sandbox()
	{

	}

};

Lotus::Application* Lotus::CreateApplication()
{
	return new Sandbox();
}