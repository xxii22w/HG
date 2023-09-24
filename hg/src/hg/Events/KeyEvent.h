#pragma once
#include "Event.h"

#include <sstream>

namespace hg {

	// 键盘事务
	class HG_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode()const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			:m_KeyCode(keycode){}
		int m_KeyCode;
	};
	// 键盘按压事务
	class HG_API KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int keycode,int repeatCount)
			:KeyEvent(keycode), m_RepeatCount(repeatCount){}

		// 重复按压次数
		inline int GetRepeatCount()const { return m_RepeatCount; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	// 键盘释放事务
	class HG_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			:KeyEvent(keycode){}

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
	};
	class HG_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			:KeyEvent(keycode){}

		// 重复按压次数
		inline int GetRepeatCount()const { return m_RepeatCount; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	private:
		int m_RepeatCount;
	};


}