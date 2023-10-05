#include "hgpch.h"
#include "Application.h"
#include "Input.h"

#include "hg/Log.h"
#include "hg/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace hg {

#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

		Application* Application::s_Instance = nullptr;

		Application::Application()
		{
			HG_CORE_ASSERT(!s_Instance, "Application already exists!");
			s_Instance = this;
			// 创建窗口
			m_Window = std::unique_ptr<Window>(Window::Create());
			m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

			Renderer::Init();

			m_ImGuiLayer = new	ImGuiLayer();
			PushOverlay(m_ImGuiLayer);

		}
		Application::~Application()
		{

		}

		void Application::PushLayer(Layer* layer)
		{
			m_LayerStack.PushLayer(layer);
			layer->OnAttach();
		}

		void Application::PushOverlay(Layer* overlay)
		{
			m_LayerStack.PushOverLay(overlay);
			overlay->OnAttach();
		}


		// 窗口开关
		void Application::OnEvent(Event& e)
		{
			// 应用调度
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

			for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
			{
				(*--it)->OnEvent(e);
				if (e.m_Handled)
					break;
			}
		}

		void Application::run()
		{
			while (m_Running)
			{
				float time = (float)glfwGetTime();
				Timestep timestep = time - m_LastFrameTime;
				m_LastFrameTime = time;
				

				for (Layer* layer : m_LayerStack) 
					layer->OnUpdate(timestep);

				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->End();
				

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