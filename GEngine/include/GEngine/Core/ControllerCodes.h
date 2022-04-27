#pragma once
#include <cstdint>

namespace GEngine
{ 
	using ControllerCode = int8_t;
	namespace Controller
	{
		typedef enum : ControllerCode
		{
			BUTTON_INVALID = -1,
			BUTTON_A = 0,
			BUTTON_B = 1,
			BUTTON_X = 2,
			BUTTON_Y = 3,
			BUTTON_BACK = 4,
			BUTTON_GUIDE = 5,
			BUTTON_START = 6,
			BUTTON_LEFTSTICK = 7,
			BUTTON_RIGHTSTICK = 8,
			BUTTON_LEFTSHOULDER = 9,
			BUTTON_RIGHTSHOULDER = 10,
			BUTTON_DPAD_UP,
			BUTTON_DPAD_DOWN,
			BUTTON_DPAD_LEFT,
			BUTTON_DPAD_RIGHT,

			//Following are XBOX, PS4/PS5, Nintendo Switch Pro specific button
			BUTTON_MISC1,         // Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button
			BUTTON_PADDLE1,       // Xbox Elite paddle P1
			BUTTON_PADDLE2,       // Xbox Elite paddle P3
			BUTTON_PADDLE3,	      // Xbox Elite paddle P2
			BUTTON_PADDLE4,	      // Xbox Elite paddle P4
			BUTTON_TOUCHPAD,      // PS4/PS5 touchpad button
			BUTTON_MAX

		} GEngineControllerCode;
	

	}
}
