#pragma once
#include <cstdint>

// from glfw3.h

//#define HG_MOUSE_BUTTON_0         0
//#define HG_MOUSE_BUTTON_1         1
//#define HG_MOUSE_BUTTON_2         2
//#define HG_MOUSE_BUTTON_3         3
//#define HG_MOUSE_BUTTON_4         4
//#define HG_MOUSE_BUTTON_5         5
//#define HG_MOUSE_BUTTON_6         6
//#define HG_MOUSE_BUTTON_7         7
//#define HG_MOUSE_BUTTON_LAST      HG_MOUSE_BUTTON_7
//#define HG_MOUSE_BUTTON_LEFT      HG_MOUSE_BUTTON_0
//#define HG_MOUSE_BUTTON_RIGHT     HG_MOUSE_BUTTON_1
//#define HG_MOUSE_BUTTON_MIDDLE    HG_MOUSE_BUTTON_2

namespace hg
{
	using MouseCode = uint16_t;

	namespace Mouse
	{
		enum : MouseCode
		{
			// From glfw3.h
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,
			Button3 = 3,
			Button4 = 4,
			Button5 = 5,
			Button6 = 6,
			Button7 = 7,

			ButtonLast = Button7,
			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2
		};
	}
}