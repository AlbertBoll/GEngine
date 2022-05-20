#pragma once
#include"Array.h"
#include <vector>
#include"ArrayAccessor1D.h"


namespace GEngine::GridBasedContainer
{
	template<typename T>
	class Array<T, 1> final  //1 dimensional array
	{
		
		typedef std::vector<T> ContainerType;
		typedef typename ContainerType::iterator Iterator;
		typedef typename ContainerType::const_iterator Const_Iterator;

	public:

		Array(){};

		explicit Array(size_t size, const T& initVal = T());

		Array(const std::initializer_list<T>& list);

		//! Copy constructor.
		Array(const Array& other);

		//! Move constructor.
		Array(Array&& other);

		//! Sets entire array with given \p value.
		Array& operator=(const T& other);

		//! Copies given array \p other to this array.
		Array& operator=(const Array& other);

		//! Move assignment.
		Array& operator=(Array&& other);

		//! Copies given initializer list \p lst to this array.
		Array& operator=(const std::initializer_list<T>& lst);

		void Set(const T& value);

		//! Copies given array \p other to this array.
		void Set(const Array& other);

		//! Copies given initializer list \p lst to this array.
		void Set(const std::initializer_list<T>& lst);

		//! Clears the array and resizes to zero.
		void Clear();

		//! Resizes the array with \p size and fill the new element with \p initVal.
		void Resize(size_t size, const T& initVal = T());

		//! Returns the reference to the i-th element.
		T& At(size_t i);

		//! Returns the const reference to the i-th element.
		const T& At(size_t i) const;

		//! Returns size of the array.
		size_t Size() const;

		//! Returns the raw pointer to the array data.
		T* Data();

		//! Returns the const raw pointer to the array data.
		const T* const Data() const;

		//! Returns the begin iterator of the array.
		Iterator begin();

		//! Returns the begin const iterator of the array.
		Const_Iterator begin() const;

		//! Returns the end iterator of the array.
		Iterator end();

		//! Returns the end const iterator of the array.
		Const_Iterator end() const;

		//! Swaps the content of the array with \p other array.
		void Swap(Array& other);

		//! Appends single value \p newVal at the end of the array.
		void Append(const T& newVal);

		//! Appends \p other array at the end of the array.
		void Append(const Array& other);

		template <typename Callback>
		void ForEach(Callback func) const;

		template <typename Callback>
		void ForEach(Callback func);

		template <typename Callback>
		void ForEachIndex(Callback func) const;

		template <typename Callback>
		void ForEachIndex(Callback func);

		template <typename Callback>
		void ParallelForEach(Callback func) const;

		template <typename Callback>
		void ParallelForEach(Callback func);

		template <typename Callback>
		void ParallelForEachIndex(Callback func) const;

		template <typename Callback>
		void ParallelForEachIndex(Callback func);

		//! Returns the reference to i-th element.
		T& operator[](size_t i);

		//! Returns the const reference to i-th element.
		const T& operator[](size_t i) const;

		//! Casts to array accessor.
		operator ArrayAccessor1D<T>();

		//! Casts to const array accessor.
		operator ConstArrayAccessor1D<T>() const;

		ArrayAccessor1D<T> Accessor();

		ConstArrayAccessor1D<T> ConstAccessor() const;

	private:
		ContainerType m_Data;

	};

	template<typename T>
	using Array1D = Array<T, 1>;



	template<typename T>
	inline Array<T, 1>::Array(size_t size, const T& initVal)
	{
		Resize(size, initVal);
	}

	template<typename T>
	inline Array<T, 1>::Array(const std::initializer_list<T>& list)
	{
		Set(list);
	}

	template<typename T>
	inline Array<T, 1>::Array(const Array& other)
	{
		Set(other);
	}

	template<typename T>
	inline Array<T, 1>::Array(Array&& other)
	{
		(*this) = std::move(other);
	}

	template<typename T>
	inline Array<T, 1>& Array<T, 1>::operator=(const T& other)
	{
		Set(other);
		return *this;
	}

	template<typename T>
	inline Array<T, 1>& Array<T, 1>::operator=(const Array& other)
	{
		Set(other);
		return *this;
	}

	template<typename T>
	inline Array<T, 1>& Array<T, 1>::operator=(Array&& other)
	{
		m_Data = std::move(other.m_Data);
		return *this;
	}


	template<typename T>
	inline Array<T, 1>& Array<T, 1>::operator=(const std::initializer_list<T>& lst)
	{
		Set(lst);
		return *this;
	}

	template<typename T>
	inline void Array<T, 1>::Set(const T& value)
	{
		for (auto& v : m_Data) v = value;
	}


	template<typename T>
	inline void Array<T, 1>::Set(const Array& other)
	{
		m_Data.resize(other.m_Data.size());
		std::copy(other.m_Data.begin(), other.m_Data.end(), m_Data.begin());
	}

	template<typename T>
	inline void Array<T, 1>::Set(const std::initializer_list<T>& lst)
	{
		size_t size = lst.size();
		Resize(size);
		auto colIter = lst.begin();
		for (size_t i = 0; i < size; ++i) {
			(*this)[i] = *colIter;
			++colIter;
		}
	}

	template<typename T>
	inline void Array<T, 1>::Clear()
	{
		m_Data.clear();
	}

	template<typename T>
	inline void Array<T, 1>::Resize(size_t size, const T& initVal)
	{
		m_Data.resize(size, initVal);
	}

	template<typename T>
	inline T& Array<T, 1>::At(size_t i)
	{
		ASSERT(i >= 0 && i < Size());
		return m_Data[i];

	}

	template<typename T>
	inline const T& Array<T, 1>::At(size_t i) const
	{
		ASSERT(i >= 0 && i < Size());
		return m_Data[i];
	}

	template<typename T>
	inline size_t Array<T, 1>::Size() const
	{
		return m_Data.size();
	}

	template<typename T>
	inline T* Array<T, 1>::Data()
	{
		return m_Data.data();
	}

	template<typename T>
	inline const T* const Array<T, 1>::Data() const
	{
		return m_Data.data();
	}

	template<typename T>
	inline typename Array<T, 1>::ContainerType::iterator Array<T, 1>::begin()
	{
		return m_Data.begin();
	}

	template<typename T>
	inline typename Array<T, 1>::ContainerType::const_iterator Array<T, 1>::begin() const
	{
		return m_Data.cbegin();
	}

	template<typename T>
	inline typename Array<T, 1>::ContainerType::iterator Array<T, 1>::end()
	{
		return m_Data.end();
	}

	template<typename T>
	inline typename Array<T, 1>::ContainerType::const_iterator Array<T, 1>::end() const
	{
		return m_Data.cend();
	}

	template<typename T>
	inline void Array<T, 1>::Swap(Array& other)
	{
		std::swap(other.m_Data, m_Data);
	}

	template<typename T>
	inline void Array<T, 1>::Append(const T& newVal)
	{
		m_Data.push_back(newVal);
	}

	template<typename T>
	inline void Array<T, 1>::Append(const Array& other)
	{
		m_Data.insert(m_Data.end(), other.m_Data.begin(), other.m_Data.end());
	}

	template<typename T>
	inline T& Array<T, 1>::operator[](size_t i)
	{
		ASSERT(i >= 0 && i < Size());
		return m_Data[i];
	}

	template<typename T>
	inline const T& Array<T, 1>::operator[](size_t i) const
	{

		ASSERT(i >= 0 && i < Size());
		return m_Data[i];
	}




	template<typename T>
	inline ArrayAccessor1D<T> Array<T, 1>::Accessor()
	{
		return ArrayAccessor1D<T>(Size(), Data());
	}

	template<typename T>
	inline ConstArrayAccessor1D<T> Array<T, 1>::ConstAccessor() const
	{
		return ConstArrayAccessor1D<T>(Size(), Data());
	}


	template<typename T>
	inline Array<T, 1>::operator ConstArrayAccessor1D<T>() const
	{
		return ConstAccessor();
	}

	template<typename T>
	inline Array<T, 1>::operator ArrayAccessor1D<T>()
	{
		return Accessor();
	}


	template<typename T>
	template<typename Callback>
	inline void Array<T, 1>::ForEach(Callback func) const
	{
		ConstAccessor().ForEach(func);
	}

	template<typename T>
	template<typename Callback>
	inline void Array<T, 1>::ForEach(Callback func)
	{
		Accessor().ForEach(func);
	}

	template<typename T>
	template<typename Callback>
	inline void Array<T, 1>::ForEachIndex(Callback func) const
	{
		ConstAccessor().ForEachIndex(func);
	}

	template<typename T>
	template<typename Callback>
	inline void Array<T, 1>::ForEachIndex(Callback func)
	{
		Accessor().ForEachIndex(func);
	}

	template<typename T>
	template<typename Callback>
	inline void Array<T, 1>::ParallelForEach(Callback func)
	{
		Accessor().ParallelForEach(func);
	}

	template<typename T>
	template<typename Callback>
	inline void Array<T, 1>::ParallelForEach(Callback func)const
	{
		ConstAccessor().ParallelForEach(func);
	}

	template<typename T>
	template<typename Callback>
	inline void Array<T, 1>::ParallelForEachIndex(Callback func) const
	{
		ConstAccessor().ParallelForEachIndex(func);
	}

	template<typename T>
	template<typename Callback>
	inline void Array<T, 1>::ParallelForEachIndex(Callback func)
	{
		Accessor().ParallelForEachIndex(func);
	}


}