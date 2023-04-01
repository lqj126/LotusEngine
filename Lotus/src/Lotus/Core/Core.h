#pragma once

#include <memory>

#ifdef LT_PLATFORM_WINDOWS
#if LT_DYNAMIC_LINK
	#ifdef LT_BUILD_DLL
		#define Lotus_API __declspec(dllexport)
	#else
		#define Lotus_API __declspec(dllimport)
	#endif
#else
    #define Lotus_API
#endif
#else
	#error Lotus only supports Windows!
#endif

#ifdef LT_DEBUG
	#define LT_ENABLE_ASSERTS
#endif

#ifdef LT_ENABLE_ASSERTS
	#define LT_ASSERT(x, ...) { if(!(x)) { LT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LT_CORE_ASSERT(x, ...) { if(!(x)) { LT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LT_ASSERT(x, ...)
	#define LT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define LT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Lotus {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
