#pragma once

#include "hg/Core/Base.h"
#include "hg/Events/Event.h"
#include "Window.h"
#include "hg/Events/ApplicationEvent.h"
#include "hg/Core/LayerStack.h"
#include "hg/Renderer/Shader.h"
#include "hg/Renderer/VertexArray.h"
#include "hg/Core/Timestep.h"

#include "hg/imGui/ImGuiLayer.h"
#include "hg/Renderer/Buffer.h"
#include "hg/Renderer/OrthographicCamera.h"



namespace hg {

	// 应用程序命令行参数
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			HG_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	class  Application
	{
	public:
		Application(const std::string& name = "hg App", ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
		virtual ~Application();
		void run();
		// 开启事务
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		inline static Application& Get() { return *s_Instance; }

		ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizedEvent& e);

	private:
		ImGuiLayer* m_ImGuiLayer;
		std::unique_ptr<Window> m_Window;
		ApplicationCommandLineArgs m_CommandLineArgs;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};
	// 在客户端实现的
	Application* CreateApplication(ApplicationCommandLineArgs args);
}

