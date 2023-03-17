#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Lotus {

	class Lotus_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define LT_CORE_TRACE(...)    ::Lotus::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LT_CORE_INFO(...)     ::Lotus::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LT_CORE_WARN(...)     ::Lotus::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LT_CORE_ERROR(...)    ::Lotus::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LT_CORE_CRITICAL(...) ::Lotus::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define LT_TRACE(...)         ::Lotus::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LT_INFO(...)          ::Lotus::Log::GetClientLogger()->info(__VA_ARGS__)
#define LT_WARN(...)          ::Lotus::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LT_ERROR(...)         ::Lotus::Log::GetClientLogger()->error(__VA_ARGS__)
#define LT_CRITICAL(...)      ::Lotus::Log::GetClientLogger()->critical(__VA_ARGS__)
