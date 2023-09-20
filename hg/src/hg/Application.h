#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "hg/Events/ApplicationEvent.h"


namespace hg {
	class HG_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
		// 开启事务
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
	// 在客户端实现的
	Application* CreateApplication();
}

