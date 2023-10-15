#include "hgpch.h"
#include "Application.h"
#include "Input.h"

#include "hg/Core/Log.h"
#include "hg/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace hg {

#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

		Application* Application::s_Instance = nullptr;

		Application::Application(const std::string& name)
		{
			HG_PROFILE_FUNCTION();

			HG_CORE_ASSERT(!s_Instance, "Application already exists!");
			s_Instance = this;
			// 创建窗口
			m_Window = Window::Create(WindowProps(name));
			m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

			Renderer::Init();

			m_ImGuiLayer = new	ImGuiLayer();
			PushOverlay(m_ImGuiLayer);

		}
		Application::~Application()
		{
			HG_PROFILE_FUNCTION();

			Renderer::Shutdown();
		}

		void Application::PushLayer(Layer* layer)
		{
			HG_PROFILE_FUNCTION();

			m_LayerStack.PushLayer(layer);
			layer->OnAttach();
		}

		void Application::PushOverlay(Layer* overlay)
		{
			HG_PROFILE_FUNCTION();

			m_LayerStack.PushOverLay(overlay);
			overlay->OnAttach();
		}

		void Application::Close()
		{
			m_Running = false;
		}


		// 窗口开关
		void Application::OnEvent(Event& e)
		{
			HG_PROFILE_FUNCTION();

			// 应用调度
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
			dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FN(OnWindowResize));


			for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend();++it)
			{
				if (e.m_Handled)
					break;
				(*it)->OnEvent(e);
			}
		}

		void Application::run()
		{
			HG_PROFILE_FUNCTION();

			while (m_Running)
			{
				HG_PROFILE_SCOPE("RunLoop");

				float time = (float)glfwGetTime();
				Timestep timestep = time - m_LastFrameTime;
				m_LastFrameTime = time;
				
				if (!m_Minimized)
				{
					{
						HG_PROFILE_SCOPE("LayerStack OnUpdata");
						for (Layer* layer : m_LayerStack)
							layer->OnUpdate(timestep);
					}

					m_ImGuiLayer->Begin();
					{
						HG_PROFILE_SCOPE("LayerStack OnImGuiRender");

						for (Layer* layer : m_LayerStack)
							layer->OnImGuiRender();
					}
					m_ImGuiLayer->End();
				}


				
				m_Window->OnUpdate();
				
			}
		}

		// 关闭窗口
		bool Application::OnWindowClose(WindowCloseEvent& e)
		{
			m_Running = false;
			return true;
		}

		bool Application::OnWindowResize(WindowResizedEvent& e)
		{
			HG_PROFILE_FUNCTION();

			if (e.GetWidth() == 0 || e.GetHeight() == 0)
			{
				m_Minimized = true;
				return false;
			}

			m_Minimized = false;
			Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

			return false;
		}
}