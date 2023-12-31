#pragma once

#include "hg/Events/Event.h"
#include "hg/Core/MouseCodes.h"
#include <sstream>

namespace hg {
	// 鼠标移动事件
	class 
		MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x,float y)
			:m_MouseX(x), m_MouseY(y){}
		
		inline float GetX()const { return m_MouseX; }
		inline float GetY()const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream a;
			a << "MouseMovedEvent: xPos = " << GetX() << ", yPos = " << GetY();
			return a.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};
	// 鼠标滑轮事件
	class  MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset,float yOffset)
			:m_XOffset(xOffset), m_YOffset(yOffset){}

		inline float GetXOffset()const { return m_XOffset; }
		inline float GetYOffset()const { return m_YOffset; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};

	// 鼠标按键事务
	class  MouseButtonEvent : public Event
	{
	/*public:
		inline int GetMouseButton()const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			:m_Button(button){}
		int m_Button;*/
	public:
		MouseCode GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
	protected:
		MouseButtonEvent(const MouseCode button)
			: m_Button(button) {}

		MouseCode m_Button;
	};

	// 按压鼠标事务
	class  MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button){}

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	// 释放鼠标事务
	class  MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			:MouseButtonEvent(button){}

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)

	};
}