#pragma once

#include "hg/Core.h"

#include <string>
#include <functional>
#include <string>

namespace hg {
	// 事件类型
	enum class EventType
	{
		None = 0,
		// 窗口事件
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		// ...
		AppTick, AppUpdate, AppRender,
		// 键盘事件
		KeyPressed, KeyReleased,KeyTyped,
		// 鼠标事件
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// 使用 位字段 来标志开启哪个事件
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::##type;}\
								virtual EventType GetEventType()const override{return GetStaticType();}\
								virtual const char* GetName()const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags()const override {return category;}

	// 事件类
	class HG_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType()const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		// 判断开启了哪一种事件
		inline bool isInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
		bool m_Handled = false;
	};

	// 事件調度程式
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F 将由编译器推导 判断类型是否一致
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// 如果一致的话，就加上这种属性
				m_Event.m_Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}