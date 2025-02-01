#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Helix {

	class HELIX_API Log
	{
	public:
		static void Init();


		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger>s_CoreLogger;
		static std::shared_ptr<spdlog::logger>s_ClientLogger;

	};
	
}


//Core Log macros
#define  HX_CORE_ERROR(...) ::Helix::Log::GetCoreLogger()->error(__VA_ARGS__)
#define  HX_CORE_WARN(...)	::Helix::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define  HX_CORE_INFO(...) ::Helix::Log::GetCoreLogger()->info(__VA_ARGS__)
#define  HX_CORE_TRACE(...) ::Helix::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define  HX_CORE_FATAL(...) ::Helix::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log macros
#define  HX_ERROR(...)	::Helix::Log::GetClientLogger()->error(__VA_ARGS__)
#define  HX_WARN(...)	::Helix::Log::GetClientLogger()->warn(__VA_ARGS__)
#define  HX_INFO(...)	::Helix::Log::GetClientLogger()->info(__VA_ARGS__)
#define  HX_TRACE(...)	::Helix::Log::GetClientLogger()->trace(__VA_ARGS__)
#define  HX_FATAL(...)	::Helix::Log::GetClientLogger()->fatal(__VA_ARGS__)




