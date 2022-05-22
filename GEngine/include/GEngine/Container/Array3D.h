#pragma once
#include"Array.h"
#include"Core/Assert.h"
#include"ArrayAccessor3D.h"

namespace GEngine::GridBasedContainer
{
	template<typename T>
	class Array<T, 3>final
	{
		typedef std::vector<T> ContainerType;
		typedef typename ContainerType::iterator Iterator;
		typedef typename ContainerType::const_iterator Const_Iterator;


	public:
		Array() {};

		explicit Array(const Dim3d& size, const T& initVal = T())
		{
			Resize(size, initVal);
		}

		explicit Array(size_t width, size_t height, size_t depth,
			const T& initVal = T())
		{
			Resize(width, height, depth, initVal);
		}

		Array(const std::initializer_list<
			std::initializer_list<std::initializer_list<T>>>& lst)
		{
			Set(lst);
		}

		//! Copy constructor.
		Array(const Array& other)
		{
			Set(other);
		}

		//! Move constructor.
		Array(Array&& other)
		{
			(*this) = std::move(other);
		}


		//! Sets entire array with given \p value.
		void Set(const T& value)
		{
			for (auto& v : m_Data) v = value;
		}

		//! Copies given array \p other to this array.
		void Set(const Array& other)
		{
			m_Data.resize(other._data.size());
			std::copy(other.m_Data.begin(), other.m_Data.end(), m_Data.begin());
			m_Size = other.m_Size;
		}

		void Set(const std::initializer_list<
			std::initializer_list<std::initializer_list<T>>>& lst)
		{
			size_t depth = lst.size();
			auto pageIter = lst.begin();
			size_t height = (depth > 0) ? pageIter->size() : 0;
			auto rowIter = pageIter->begin();
			size_t width = (height > 0) ? rowIter->size() : 0;
			Resize(Dim3d(width, height, depth));
			for (size_t k = 0; k < depth; ++k) {
				rowIter = pageIter->begin();
				ASSERT(height == pageIter->size());
				for (size_t j = 0; j < height; ++j) {
					auto colIter = rowIter->begin();
					ASSERT(width == rowIter->size());
					for (size_t i = 0; i < width; ++i) {
						(*this)(i, j, k) = *colIter;
						++colIter;
					}
					++rowIter;
				}
				++pageIter;
			}
		}

		//! Clears the array and resizes to zero.
		void Clear()
		{
			m_Data.clear();
			m_Size = { 0, 0, 0 };
		}

		//! Resizes the array with \p size and fill the new element with \p initVal.
		void Resize(const Dim3d& size, const T& initVal = T())
		{
			Array grid;
			grid.m_Data.resize(size.m_Width * size.m_Height * size.m_Depth, initVal);
			grid.m_Size = size;
			size_t iMin = std::min(size.m_Width, m_Size.m_Width);
			size_t jMin = std::min(size.m_Height, m_Size.m_Height);
			size_t kMin = std::min(size.m_Depth, m_Size.m_Depth);
			for (size_t k = 0; k < kMin; ++k) {
				for (size_t j = 0; j < jMin; ++j) {
					for (size_t i = 0; i < iMin; ++i) {
						grid(i, j, k) = At(i, j, k);
					}
				}
			}

			Swap(grid);
		}

		//! Resizes the array with size \p width x \p height and fill the new
		//! element with \p initVal.
		void Resize(size_t width, size_t height, size_t depth,
			const T& initVal = T())
		{
			Resize(Dim3d{ .m_Width = width, .m_Height = height, .m_Depth = depth }, initVal);
		}


		T& At(size_t i)
		{
			ASSERT(i >= 0 && i < m_Size.m_Width* m_Size.m_Height* m_Size.m_Depth);
			return m_Data[i];
		}


		const T& At(size_t i) const
		{
			ASSERT(i >= 0 && i < m_Size.m_Width* m_Size.m_Height* m_Size.m_Depth);
			return m_Data[i];
		}

		//! Returns the reference to the element at (i, j, k).
		T& At(size_t i, size_t j, size_t k)
		{
			ASSERT(i >= 0 && i < m_Size.m_Width&&
				   j >= 0 && j < m_Size.m_Height&&
				   k >= 0 && k < m_Size.m_Depth);

			return m_Data[i + m_Size.m_Width * (j + m_Size.m_Height * k)];
		}


		//! Returns the const reference to the element at (i, j, k).
		const T& At(size_t i, size_t j, size_t k) const
		{
			ASSERT(i >= 0 && i < m_Size.m_Width&&
				   j >= 0 && j < m_Size.m_Height&&
				   k >= 0 && k < m_Size.m_Depth);

			return m_Data[i + m_Size.m_Width * (j + m_Size.m_Height * k)];
		}

		//! Returns the size of the array.
		Dim3d Size() const
		{
			return m_Size;
		}

		//! Returns the width of the array.
		size_t Width() const
		{
			return m_Size.m_Width;
		}

		//! Returns the height of the array.
		size_t Height() const
		{
			return m_Size.m_Height;
		}

		//! Returns the depth of the array.
		size_t Depth() const
		{
			return m_Size.m_Depth;
		}

		//! Returns the raw pointer to the array data.
		T* Data() { return m_Data.data(); };

		//! Returns the const raw pointer to the array data.
		const T* const Data() const { return m_Data.data(); };

		//! Returns the begin iterator of the array.
		Iterator begin() { return m_Data.begin(); }

		//! Returns the begin const iterator of the array.
		Const_Iterator begin() const { return m_Data.cbegin(); }

		//! Returns the end iterator of the array.
		Iterator end() { return m_Data.end(); }

		//! Returns the end const iterator of the array.
		Const_Iterator end() const { return m_Data.cend(); }


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
		void ForEachIndex(Callback func) const
		{
			ReadAccessor().ForEachIndex(func);
		}

		template <typename Callback>
		void ForEachIndex(Callback func)
		{
			WriteAccessor().ForEachIndex(func);
		}


		template <typename Callback>
		void ParallelForEach(Callback func)const
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

		template <typename Callback>
		void ParallelForIndexRange(Callback func)const
		{
			ReadAccessor().ParallelForIndexRange(func);
		}

		template <typename Callback>
		void ParallelForIndexRange(Callback func)
		{
			WriteAccessor().ParallelForIndexRange(func);
		}

		T& operator[](size_t i)
		{
			return m_Data[i];
		}

		const T& operator[](size_t i) const{ return m_Data[i]; }

		//! Returns the reference to the element at (i, j, k).
		T& operator()(size_t i, size_t j, size_t k)
		{
			return m_Data[i + m_Size.m_Width * (j + m_Size.m_Height * k)];
		}

		//! Returns the const reference to the element at (i, j, k).
		const T& operator()(size_t i, size_t j, size_t k) const
		{
			return m_Data[i + m_Size.m_Width * (j + m_Size.m_Height * k)];
		}

		//! Sets entire array with given \p value.
		Array& operator=(const T& value)
		{
			Set(value);
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
			other.m_Size = { 0, 0, 0 };
			return *this;
		}

		Array& operator=(const std::initializer_list<
			std::initializer_list<std::initializer_list<T>>>& lst)
		{
			Set(lst);
			return *this;
		}

		ReadAccessor3D<T> ReadAccessor() const
		{
			return ReadAccessor3D<T>(Size(), Data());
		}

		WriteAccessor3D<T> WriteAccessor()
		{
			return WriteAccessor3D<T>(Size(), Data());
		}

		operator WriteAccessor3D<T>()
		{
			return WriteAccessor();
		}

		operator ReadAccessor3D<T>()const
		{
			return ReadAccessor();
		}




	private:
		Dim3d m_Size;
		ContainerType m_Data;

	};

	//! Type alias for 3-D array.
	template <typename T>
	using Array3D = Array<T, 3>;

}