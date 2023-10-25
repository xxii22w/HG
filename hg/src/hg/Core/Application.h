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


int main(int argc, char** argv);

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

	struct ApplicationSpecification
	{
		std::string Name = "hg Application";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class  Application
	{
	public:
		Application(const ApplicationSpecification& specification);

		virtual ~Application();
		
		// 开启事务
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		static Application& Get() { return *s_Instance; }

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		void run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizedEvent& e);

	private:
		ApplicationSpecification m_Specification;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};
	// 在客户端实现的
	Application* CreateApplication(ApplicationCommandLineArgs args);
}

