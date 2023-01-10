#pragma once

#ifdef LT_PLATFORM_WINDOWS

extern Lotus::Application* Lotus::CreateApplication();

void main(int argc, char** argv)
{
	auto app = Lotus::CreateApplication();
	app->Run();
	delete app;
}
//#else
//	#error Lotus only support Windows!
#endif

