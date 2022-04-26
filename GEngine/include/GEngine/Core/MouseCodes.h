#pragma once
#include <cstdint>

namespace GEngine
{
	using MouseCodes = uint8_t;

	namespace Mouse
	{
		typedef enum : MouseCodes
		{
			BUTTON_LEFT = 1,
			BUTTON_MIDDLE = 2,
			BUTTON_RIGHT = 3
		} GEngineMouseCode;
	}
}
