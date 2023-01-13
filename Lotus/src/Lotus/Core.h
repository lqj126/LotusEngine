#pragma once

#ifdef LT_PLATFORM_WINDOWS
	#ifdef LT_BUILD_DLL
		#define LOTUS_API __declspec(dllexport)
	#else
		#define LOTUS_API __declspec(dllimport)
	#endif
#else
	#error Lotus only support Windows!
#endif

#define BIT(x) (1 << x)