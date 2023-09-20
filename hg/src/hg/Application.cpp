#include "hgpch.h"
#include "Application.h"
#include "hg/Events/ApplicationEvent.h"
#include "hg/Log.h"
#include <GLFW/glfw3.h>

namespace hg {

#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

		Application::Application()
		{
			// 创建窗口
			m_Window = std::unique_ptr<Window>(Window::Create());
			m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		}
		Application::~Application()
		{

		}

		// 窗口开关
		void Application::OnEvent(Event& e)
		{
			// 应用调度
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

			HG_CORE_TRACE("{0}",e);
		}

		void Application::run()
		{
			while (m_Running)
			{
				glClearColor(1, 0, 1, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				m_Window->OnUpdate();
			}
		}

		// 关闭窗口
		bool Application::OnWindowClose(WindowCloseEvent& e)
		{
			m_Running = false;
			return true;
		}
}