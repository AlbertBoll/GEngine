#pragma once
#include <vector>
#include <cstdint>

namespace GEngine::GridBasedContainer
{
	struct Dim2d
	{
		size_t m_Width{};
		size_t m_Height{};
	};

	struct Dim3d
	{
		size_t m_Width{};
		size_t m_Height{};
		size_t m_Depth{};
	};

	template<typename T, uint8_t N> requires(N >= 1 && N <= 3)
	class Array final  //mark Array as final which can not be inherited
	{
	public:
	
	};

	template <typename T, uint8_t N> requires(N >= 1 && N <= 3)
	class ArrayAccessor final {
	public:
	
	};

	template <typename T, uint8_t N> requires(N >= 1 && N <= 3)
	class ConstArrayAccessor final {
	public:
	
	};



}


