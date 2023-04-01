#pragma once

#ifdef LT_PLATFORM_WINDOWS

extern Lotus::Application* Lotus::CreateApplication();

int main(int argc, char** argv)
{
	Lotus::Log::Init();
	LT_CORE_WARN("Initialized Log!");

	auto app = Lotus::CreateApplication();
	app->Run();
	delete app;
}

#endif