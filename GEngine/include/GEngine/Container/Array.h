#pragma once

namespace GEngine::GridBasedContainer
{

	template<typename T, uint8_t N>
	class Array final  //mark Array as final which can not be inherited
	{
	public:
		Array()
		{
			ASSERT(N >= 1 && N <= 3, "N should be either 1, 2 or 3.");
		}
	};

	template <typename T, uint8_t N>
	class ArrayAccessor final {
	public:
		ArrayAccessor()
		{
			ASSERT(N >= 1 && N <= 3, "N should be either 1, 2 or 3.");
		}
	};

	template <typename T, uint8_t N>
	class ConstArrayAccessor final {
	public:
		ConstArrayAccessor()
		{
			ASSERT(N >= 1 && N <= 3, "N should be either 1, 2 or 3.");
		}
	};



}


