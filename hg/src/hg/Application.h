#pragma once

#include "Core.h"
#include "hg/Events/Event.h"
#include "Window.h"
#include "hg/Events/ApplicationEvent.h"
#include "hg/LayerStack.h"

#include "hg/imGui/ImGuiLayer.h"


namespace hg {
	class HG_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
		// 开启事务
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		ImGuiLayer* m_ImGuiLayer;
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};
	// 在客户端实现的
	Application* CreateApplication();
}

