#pragma once

#include "hgpch.h"
#include "Log.h"

#include <vector>


namespace hg {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		
		spdlog::set_pattern("%^[%T] %n: %v%$");				// 设置日志格式
		s_CoreLogger = spdlog::stdout_color_mt("HG");		// 创建彩色多线程日志
		s_CoreLogger->set_level(spdlog::level::trace);		// 设置警告等级

		s_ClientLogger = spdlog::stderr_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);

	}
}