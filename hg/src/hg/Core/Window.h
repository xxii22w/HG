#pragma once 

#include "hgpch.h"
#include "hg/Core/Base.h"

#include "hg/Events/Event.h"


namespace hg {

	// 窗口支撑
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "hg Engine", uint32_t width = 1600, uint32_t height = 900)
			: Title(title), Width(width), Height(height) {}
	};

	// 基于window系统的窗口界面
	class  Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window(){}

		// 更新
		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth()const = 0;
		virtual uint32_t GetHeight()const = 0;

		// 窗口属性
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		// 设置垂直同步
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync()const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}