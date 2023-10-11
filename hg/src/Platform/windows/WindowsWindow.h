#pragma once

#include "hg/Core/Window.h"

#include <GLFW/glfw3.h>
#include "hg/Renderer/GraphicsContext.h"

namespace hg {

	// windows下的窗口
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth()const override{return m_Data.Width;}
		inline unsigned int GetHeight()const override { return m_Data.Height; }

		// 窗口属性
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
		WindowData m_Data;

	};
}