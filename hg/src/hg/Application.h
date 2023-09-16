#pragma once

#include "Core.h"

namespace hg {
	class HG_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
	};
	// 在客户端实现的
	Application* CreateApplication();
}

