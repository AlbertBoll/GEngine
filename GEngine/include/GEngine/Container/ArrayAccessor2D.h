#pragma once
#include"Array.h"
#include"Core/Parallel.h"

namespace GEngine::GridBasedContainer
{
	template<typename T>
	class ArrayAccessor<T, 2> final
	{

	public:
		ArrayAccessor():m_Data{nullptr}{};

		ArrayAccessor(const Dim2d& size, T* const data)
		{
			Reset(size, data);
		}

		ArrayAccessor(size_t width, size_t height, T* const data)
		{
			Reset(width, height, data);
		}

		//! Copy constructor.
		ArrayAccessor(const ArrayAccessor& other)
		{
			Set(other);
		}

		//! Replaces the content with given \p other array accessor.
		void Set(const ArrayAccessor& other)
		{
			Reset(other.m_Size, other.m_Data);
		}

		//! Resets the array.
		void Reset(const Dim2d& size, T* const data)
		{
			m_Size = size;
			m_Data = data;
		}

		//! Resets the array.
		void Reset(size_t width, size_t height, T* const data)
		{
			Reset(Dim2d{ .m_Width = width, .m_Height = height }, data);
		}

		//! Returns the reference to the i-th element.
		T& At(size_t i)
		{
			ASSERT(i >= 0 && i < m_Size.m_Width * m_Size.m_Height);
			return m_Data[i];
		}

		//! Returns the const reference to the i-th element.
		const T& At(size_t i) const
		{
			ASSERT(i >= 0 && i < m_Size.m_Width* m_Size.m_Height);
			return m_Data[i];
		}

		//! Returns the reference to the element at (i, j).
		T& At(size_t i, size_t j)
		{
			ASSERT(i >= 0 && i < m_Size.m_Width&& j >= 0 && j < m_Size.m_Height);
			return m_Data[i + j * m_Size.m_Width];
		}

		//! Returns the const reference to the element at (i, j).
		const T& At(size_t i, size_t j) const
		{
			ASSERT(i >= 0 && i < m_Size.m_Width&& j >= 0 && j < m_Size.m_Height);
			return m_Data[i + j * m_Size.m_Width];
		}

		//! Returns the begin iterator of the array.
		T* const begin() const { return m_Data; }

		//! Returns the end iterator of the array.
		T* const end() const { return m_Data + m_Size.m_Width * m_Size.m_Height; }

		//! Returns the begin iterator of the array.
		T* begin() { return m_Data; }

		//! Returns the end iterator of the array.
		T* end() { return m_Data + m_Size.m_Width * m_Size.m_Height; }

		//! Returns the size of the array.
		Dim2d Size() const { return m_Size; }

		//! Returns the width of the array.
		size_t Width() const { return m_Size.m_Width; }

		//! Returns the height of the array.
		size_t Height() const { return m_Size.m_Height; }

		//! Returns the raw pointer to the array data.
		T* const Data() const { return m_Data; }

		//! Swaps the content of with \p other array accessor.
		void Swap(ArrayAccessor& other)
		{
			std::swap(other.m_Data, m_Data);
			std::swap(other.m_Size, m_Size);
		}

		template <typename Callback>
		void ForEach(Callback func)
		{
			for (size_t j = 0; j < m_Size.m_Height; ++j) {
				for (size_t i = 0; i < m_Size.m_Width; ++i) {
					func((*this)(i, j));
				}
			}
		}

		template <typename Callback>
		void ForEachIndex(Callback func)
		{
			for (size_t j = 0; j < m_Size.m_Height; ++j) {
				for (size_t i = 0; i < m_Size.m_Width; ++i) {
					func(i, j);
				}
			}
		}

		template <typename Callback>
		void ParallelForEach(Callback func)
		{
			ParallelFor((size_t)0, m_Size.m_Width,
				(size_t)0, m_Size.m_Height,
				[&](size_t i, size_t j) {func((*this)(i, j)); });
		}

		template <typename Callback>
		void ParallelForEachIndex(Callback func)
		{
			ParallelFor((size_t)0, m_Size.m_Width,
				(size_t)0, m_Size.m_Height, func);
		}

		template <typename Callback>
		void ParallelForIndexRange(Callback func)
		{
			ParallelRangeFor((size_t)0, m_Size.m_Width, (size_t)0, m_Size.m_Height, func);
		}

		template <typename Callback, typename Partitioner = tbb::auto_partitioner>
		void ParallelForIndexRange(const RangeParams<size_t>& xRange, const RangeParams<size_t>& yRange, Callback func, const Partitioner& partitioner = tbb::auto_partitioner{})
		{
			ParallelRangeFor(xRange, yRange, func, partitioner);
		}


		//! Returns the linear index of the given 2-D coordinate (i, j).
		size_t Index(size_t i, size_t j) const
		{
			ASSERT(i >= 0 && i < m_Size.m_Width&& j >= 0 && j < m_Size.m_Height);
			return i + j * m_Size.m_Width;
		}

		//! Returns the reference to the i-th element.
		T& operator[](size_t i) { return m_Data[i]; }

		//! Returns the const reference to the i-th element.
		const T& operator[](size_t i) const { return m_Data[i]; }

		//! Returns the reference to the element at (i, j).
		T& operator()(size_t i, size_t j) { return m_Data[i + j * m_Size.m_Width]; };

		//! Returns the const reference to the element at (i, j).
		const T& operator()(size_t i, size_t j) const { return m_Data[i + j * m_Size.m_Width]; }

		//! Copies given array accessor \p other.
		ArrayAccessor& operator=(const ArrayAccessor& other)
		{
			Set(other);
			return *this;
		}

		//! Casts type to ConstArrayAccessor.
		operator ConstArrayAccessor<T, 2>() const
		{
			return ConstArrayAccessor<T, 2>(*this);
		}

	private:
		Dim2d m_Size;
		T* m_Data;

	};

	template <typename T> 
	using WriteAccessor2D = ArrayAccessor<T, 2>;

	template<typename T>
	class ConstArrayAccessor<T, 2>
	{

	public:
		//! Constructs read-only array accessor.
		ConstArrayAccessor() :m_Data{nullptr} {};

		ConstArrayAccessor(const Dim2d& size, const T* const data)
		{
			m_Size = size;
			m_Data = data;
		}

		ConstArrayAccessor(size_t width, size_t height, const T* const data)
		{
			m_Size = Dim2d{ width, height };
			m_Data = data;

		}

		//! Constructs a read-only array accessor from read/write accessor.
		explicit ConstArrayAccessor(const ArrayAccessor<T, 2>& other)
		{
			m_Size = other.Size();
			m_Data = other.Data();
		}

		//! Copy constructor.
		ConstArrayAccessor(const ConstArrayAccessor& other)
		{
			m_Size = other.m_Size;
			m_Data = other.m_Data;
		}

		//! Returns the reference to the i-th element.
		const T& At(size_t i) const
		{
			ASSERT(i >= 0 && i < m_Size.m_Width * m_Size.m_Height);
			return m_Data[i];
		}

		//! Returns the const reference to the element at (i, j).
		const T& At(size_t i, size_t j) const
		{
			ASSERT(i >= 0 && i < m_Size.m_Width && j >= 0 && j < m_Size.m_Height);
			return m_Data[i + j * m_Size.m_Width];
		}

		//! Returns the begin iterator of the array.
		const T* const begin() const { return m_Data; }

		//! Returns the end iterator of the array.
		const T* const end() const 
		{ 
			return m_Data + m_Size.m_Width * m_Size.m_Height; 
		}

		//! Returns the size of the array.
		Dim2d Size() const { return m_Size; }

		//! Returns the width of the array.
		size_t Width() const { return m_Size.m_Width; }

		//! Returns the height of the array.
		size_t Height() const { return m_Size.m_Height; }

		//! Returns the raw pointer to the array data.
		const T* const Data() const { return m_Data; }

		template <typename Callback>
		void ForEach(Callback func) const
		{
			for (size_t j = 0; j < m_Size.m_Height; ++j)
			{
				for (size_t i = 0; i < m_Size.m_Width; ++i)
				{
					func((*this)(i, j));
				}
			}
		}

		template <typename Callback>
		void ForEachIndex(Callback func) const
		{
			for (size_t j = 0; j < m_Size.m_Height; ++j)
			{
				for (size_t i = 0; i < m_Size.m_Width; ++i)
				{
					func(i, j);
				}
			}
		}

		template <typename Callback>
		void ParallelForEach(Callback func) const
		{
			ParallelFor((size_t)0, m_Size.m_Width, 
						(size_t)0, m_Size.m_Height, 
				[&](size_t i, size_t j) {func((*this)(i, j)); });
		}

		template <typename Callback>
		void ParallelForEachIndex(Callback func) const
		{
			ParallelFor((size_t)0, m_Size.m_Width, (size_t)0, m_Size.m_Height, func);
		}

		template <typename Callback>
		void ParallelForIndexRange(Callback func) const
		{
			ParallelRangeFor((size_t)0, m_Size.m_Width, (size_t)0, m_Size.m_Height, func);
		}

		template <typename Callback, typename Partitioner = tbb::auto_partitioner>
		void ParallelForIndexRange(const RangeParams<size_t>& xRange, const RangeParams<size_t>& yRange, Callback func, const Partitioner& partitioner = tbb::auto_partitioner{}) const
		{
			ParallelRangeFor(xRange, yRange, func, partitioner);
		}


		size_t Index(size_t i, size_t j) const
		{
			ASSERT(i >= 0 && i < m_Size.m_Width&& j >= 0 && j < m_Size.m_Height);
			return i + j * m_Size.m_Width;
		}

		//! Returns the const reference to the i-th element.
		const T& operator[](size_t i) const { return m_Data[i]; };

		//! Returns the const reference to the element at (i, j).
		const T& operator()(size_t i, size_t j) const
		{
			return m_Data[i + j * m_Size.m_Width];
		}

	private:
		Dim2d m_Size;
		const T* m_Data;


	};

	// !Type alias for 2 - D const array accessor.
	template <typename T> 
	using ReadAccessor2D = ConstArrayAccessor<T, 2>;

}
