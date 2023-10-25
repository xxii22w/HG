#pragma once
#include "Event.h"
#include "hg/Core/KeyCode.h"
#include <sstream>

namespace hg {

	// 键盘事务
	class 
		KeyEvent : public Event
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
	class  KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(const KeyCode keycode,int repeatCount)
			:KeyEvent(keycode), m_IsRepeat(repeatCount){}

		// 重复按压次数
		bool IsRepeat() const { return m_IsRepeat; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		bool m_IsRepeat;
	};

	// 键盘释放事务
	class  KeyReleasedEvent : public KeyEvent
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
	class  KeyTypedEvent : public KeyEvent
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