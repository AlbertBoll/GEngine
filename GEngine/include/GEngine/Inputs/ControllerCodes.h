#pragma once
#include <cstdint>

namespace GEngine::Input
{ 
	using ControllerCode = int8_t;
	namespace Controller
	{
		typedef enum : ControllerCode
		{
			GENGINE_BUTTON_INVALID = -1,
			GENGINE_BUTTON_A = 0,
			GENGINE_BUTTON_B = 1,
			GENGINE_BUTTON_X = 2,
			GENGINE_BUTTON_Y = 3,
			GENGINE_BUTTON_BACK = 4,
			GENGINE_BUTTON_GUIDE = 5,
			GENGINE_BUTTON_START = 6,
			GENGINE_BUTTON_LEFTSTICK = 7,
			GENGINE_BUTTON_RIGHTSTICK = 8,
			GENGINE_BUTTON_LEFTSHOULDER = 9,
			GENGINE_BUTTON_RIGHTSHOULDER = 10,
			GENGINE_BUTTON_DPAD_UP,
			GENGINE_BUTTON_DPAD_DOWN,
			GENGINE_BUTTON_DPAD_LEFT,
			GENGINE_BUTTON_DPAD_RIGHT,

			//Following are XBOX, PS4/PS5, Nintendo Switch Pro specific button
			GENGINE_BUTTON_MISC1,         // Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button
			GENGINE_BUTTON_PADDLE1,       // Xbox Elite paddle P1
			GENGINE_BUTTON_PADDLE2,       // Xbox Elite paddle P3
			GENGINE_BUTTON_PADDLE3,	      // Xbox Elite paddle P2
			GENGINE_BUTTON_PADDLE4,	      // Xbox Elite paddle P4
			GENGINE_BUTTON_TOUCHPAD,      // PS4/PS5 touchpad button
			GENGINE_BUTTON_MAX

		} GEngineControllerCode;
	

	}
}
