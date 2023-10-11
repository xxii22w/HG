#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace hg {
	class HG_API Log
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

// 核心日志宏
#define HG_CORE_ERROR(...)	::hg::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HG_CORE_WARN(...)	::hg::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HG_CORE_INFO(...)	::hg::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HG_CORE_TRACE(...)	::hg::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HG_CORE_FATAL(...)	::hg::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// 客户端日志宏
#define HG_ERROR(...)		::hg::Log::GetClientLogger()->error(__VA_ARGS__)
#define HG_WARN(...)		::hg::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HG_INFO(...)		::hg::Log::GetClientLogger()->info(__VA_ARGS__)
#define HG_TRACE(...)		::hg::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HG_FATAL(...)		::hg::Log::GetClientLogger()->fatal(__VA_ARGS__)

