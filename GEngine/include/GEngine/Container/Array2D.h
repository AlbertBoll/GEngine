#pragma once
#include"Array.h"
#include"ArrayAccessor2D.h"
#include<vector>

namespace GEngine::GridBasedContainer
{
	template<typename T>
	class Array<T, 2>final
	{
		typedef std::vector<T> ContainerType;
		typedef typename ContainerType::iterator Iterator;
		typedef typename ContainerType::const_iterator Const_Iterator;


	public:

		Array() {};
		explicit Array(const Dim2d& size, const T& initVal = T())
		{
			Resize(size, initVal);
		}

		Array(size_t width, size_t height, const T& initVal = T())
		{
			Resize(width, height, initVal);
		}

		Array(const std::initializer_list<std::initializer_list<T>>& lst)
		{
			Set(lst);
		}

		//! Copy constructor.
		Array(const Array& other) { Set(other); }

		//! Move constructor.
		Array(Array&& other) { (*this) = std::move(other); }

		//! Sets entire array with given \p value.
		void Set(const T& value)
		{
			for (auto& v : m_Data) v = value;
		}

		//! Copies given array \p other to this array.
		void Set(const Array& other)
		{
			m_Data.resize(other.m_Data.size);
			std::copy(other.m_Data.begin(), other.m_Data.end(), m_Data.begin());
			m_Size = other.m_Size;
		}

		void Set(const std::initializer_list<std::initializer_list<T>>& lst)
		{
			size_t height = lst.size();
			size_t width = (height > 0) ? lst.begin()->size() : 0;
			Resize(Dim2d{ width, height });

			auto rowIter = lst.begin();
			for (size_t j = 0; j < height; ++j) {
				ASSERT(width == rowIter->size());
				auto colIter = rowIter->begin();
				for (size_t i = 0; i < width; ++i) {
					(*this)(i, j) = *colIter;
					++colIter;
				}
				++rowIter;
			}

		}

		//! Clears the array and resizes to zero.
		void Clear()
		{
			m_Data.clear();
			m_Size = { 0, 0 };
		}

		//! Resizes the array with \p size and fill the new element with \p initVal.
		void Resize(const Dim2d& size, const T& initVal = T())
		{
			Array grid;
			grid.m_Data.resize(size.m_Width * size.m_Height, initVal);
			grid.m_Size = size;
			size_t iMin = std::min(size.m_Width, m_Size.m_Width);
			size_t jMin = std::min(size.m_Height, m_Size.m_Height);
			for (size_t j = 0; j < jMin; ++j) {
				for (size_t i = 0; i < iMin; ++i) {
					grid(i, j) = At(i, j);
				}
			}

			Swap(grid);
		}

		//! Resizes the array with size \p width x \p height and fill the new
		//! element with \p initVal.
		void Resize(size_t width, size_t height, const T& initVal = T())
		{
			Resize(Dim2d{ width, height }, initVal);
		}

		T& At(size_t i)
		{
			ASSERT(i >= 0 && i < m_Size.m_Width * m_Size.m_Height);
			return m_Data[i];
		}

		const T& At(size_t i) const
		{
			ASSERT(i >= 0 && i < m_Size.m_Width * m_Size.m_Height);
			return m_Data[i];
		}

		//! Returns the reference to the element at (i, j).
		T& At(size_t i, size_t j)
		{
			ASSERT(i >= 0 && i < m_Size.m_Width && j >= 0 && j < m_Size.m_Height);
			return m_Data[i + j * m_Size.m_Width];
		}

		const T& At(size_t i, size_t j)const
		{
			ASSERT(i >= 0 && i < m_Size.m_Width && j >= 0 && j < m_Size.m_Height);
			return m_Data[i + j * m_Size.m_Width];
		}


		Dim2d Size()const { return m_Size; }

		//! Returns the width of the array.
		size_t Width() const { return m_Size.m_Width; }

		//! Returns the height of the array.
		size_t Height() const { return m_Size.m_Height; }

		//! Returns the raw pointer to the array data.
		T* Data() { return m_Data; }

		//! Returns the const raw pointer to the array data.
		const T* const Data() const { return m_Data; }

		//! Returns the begin iterator of the array.
		Iterator begin() { return m_Data.begin(); }

		//! Returns the begin const iterator of the array.
		Const_Iterator begin() const { return m_Data.cbegin(); }

		//! Returns the end iterator of the array.
		Iterator end() { return m_Data.end(); }

		//! Returns the end const iterator of the array.
		Const_Iterator end() const { return m_Data.cend(); }

		T& operator[](size_t i) { return m_Data[i]; }

		const T& operator[](size_t i) const
		{
			return m_Data[i];
		}
	

		//! Returns the reference to the element at (i, j).
		T& operator()(size_t i, size_t j) { return At(i, j); }

		//! Returns the const reference to the element at (i, j).
		const T& operator()(size_t i, size_t j) const { return At(i, j); }

		//! Sets entire array with given \p value.
		Array& operator=(const T& other)
		{
			Set(other);
			return *this;
		}

		//! Copies given array \p other to this array.
		Array& operator=(const Array& other)
		{
			Set(other);
			return *this;
		}

		//! Move assignment.
		Array& operator=(Array&& other)
		{
			m_Data = std::move(other.m_Data);
			m_Size = other.m_Size;
			other.m_Size = { 0, 0 };
			return *this;
		}

		Array& operator=(const std::initializer_list<std::initializer_list<T>>& lst)
		{
			Set(lst);
			return *this;
		}

		//! Swaps the content of the array with \p other array.
		void Swap(Array& other)
		{
			std::swap(other.m_Data, m_Data);
			std::swap(other.m_Size, m_Size);
		}

		template <typename Callback>
		void ForEach(Callback func) const
		{
			ReadAccessor().ForEach(func);
		}

		template <typename Callback>
		void ForEach(Callback func)
		{
			WriteAccessor().ForEach(func);
		}

		template <typename Callback>
		void ForEachIndex(Callback func) const {
			ReadAccessor().ForEachIndex(func);
		}

		template <typename Callback>
		void ForEachIndex(Callback func)
		{
			WriteAccessor().ForEachIndex(func);
		}

		template <typename Callback>
		void ParallelForEach(Callback func) const
		{
			ReadAccessor().ParallelForEach(func);
		}

		template <typename Callback>
		void ParallelForEach(Callback func)
		{
			WriteAccessor().ParallelForEach(func);
		}
		

		template <typename Callback>
		void ParallelForEachIndex(Callback func) const
		{
			ReadAccessor().ParallelForEachIndex(func);
		}


		template <typename Callback>
		void ParallelForEachIndex(Callback func)
		{
			WriteAccessor().ParallelForEachIndex(func);
		}


		WriteAccessor2D<T> WriteAccessor()
		{
			return WriteAccessor2D<T>(Size(), Data());
		}

		ReadAccessor2D<T> ReadAccessor() const
		{
			return ReadAccessor2D<T>(Size(), Data());
		}

		//! Casts to array accessor.
		operator WriteAccessor2D<T>() 
		{	
			return WriteAccessor();
		}

		//! Casts to const array accessor.
		operator ReadAccessor2D<T>() const
		{
			return ReadAccessor();
		}


	private:
		Dim2d m_Size;
		std::vector<T> m_Data;

	};

	template<typename T>
	using Array2D = Array<T, 2>;
}
