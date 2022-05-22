#pragma once
#include"Core/Parallel.h"

namespace GEngine::GridBasedContainer
{
	template<typename T>
	class ArrayAccessor<T, 3> final
	{

	public:
		ArrayAccessor() :m_Data{ nullptr } {};

		ArrayAccessor(const Dim3d& size, T* const data)
        {
            Reset(size, data);
        }

        ArrayAccessor(size_t width, size_t height, size_t depth, T* const data)
        {
            Reset(width, height, depth, data);
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
        void Reset(const Dim3d& size, T* const data)
        {
            m_Data = data;
            m_Size = size;
        }

        //! Resets the array.
        void Reset(size_t width, size_t height, size_t depth, T* const data)
        {
            m_Data = data;
            m_Size = Dim3d{ width, height, depth };
        }

        //! Returns the reference to the i-th element.
        T& At(size_t i)
        {
            ASSERT(i >= 0 && i < m_Size.m_Width* m_Size.m_Height* m_Size.m_Depth);
            return m_Data[i];
        }

        //! Returns the const reference to the i-th element.
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

        //! Returns the begin iterator of the array.
        T* const begin() const
        {
            return m_Data;
        }

        //! Returns the end iterator of the array.
        T* const end() const
        {
            return m_Data + m_Size.m_Width * m_Size.m_Height * m_Size.m_Depth;
        }

        //! Returns the begin iterator of the array.
        T* begin()
        {
            return m_Data;
        }

        //! Returns the end iterator of the array.
        T* end()
        {
            return m_Data + m_Size.m_Width * m_Size.m_Height * m_Size.m_Depth;
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
        T* const Data() const
        {
            return m_Data;
        }

        template <typename Callback>
        void ForEach(Callback func)
        {
            for (size_t k = 0; k < m_Size.m_Depth; ++k) {
                for (size_t j = 0; k < m_Size.m_Height; ++j) {
                    for (size_t i = 0; k < m_Size.m_Width; ++i)
                    {
                        func((*this)(i, j, k));
                    }
                }
            }
        }

        template <typename Callback>
        void ForEachIndex(Callback func)
        {
            for (size_t k = 0; k < m_Size.m_Depth; ++k) {
                for (size_t j = 0; k < m_Size.m_Height; ++j) {
                    for (size_t i = 0; k < m_Size.m_Width; ++i)
                    {
                        func(i, j, k);
                    }
                }
            }
        }

        template <typename Callback>
        void ParallelForEach(Callback func)
        {
            ParallelFor((size_t)0, m_Size.m_Width,
                        (size_t)0, m_Size.m_Height,
                        (size_t)0, m_Size.m_Depth,
                        [&](size_t i, size_t j, size_t k) 
                        {
                            func((*this)(i, j, k)); 
                        });
        }

        template <typename Callback>
        void ParallelForEachIndex(Callback func)
        {
            ParallelFor((size_t)0, m_Size.m_Width,
                (size_t)0, m_Size.m_Height,
                (size_t)0, m_Size.m_Depth,
                func);
        }

        template <typename Callback>
        void ParallelForIndexRange(Callback func)
        {
            ParallelRangeFor((size_t)0, m_Size.m_Width, (size_t)0, m_Size.m_Height, (size_t)0, m_Size.m_Depth, func);
        }


        //! Returns the linear index of the given =3-D coordinate (i, j, k).
        size_t Index(size_t i, size_t j, size_t k) const
        {
            return i + m_Size.m_Width * (j + m_Size.m_Height * k);
        }

        //! Returns the reference to the i-th element.
        T& operator[](size_t i)
        {
            return m_Data[i];
        }

        //! Returns the const reference to the i-th element.
        const T& operator[](size_t i) const
        {
            return m_Data[i];
        }

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

        //! Swaps the content of with \p other array accessor.
        void Swap(ArrayAccessor& other)
        {
            std::swap(other.m_Data, m_Data);
            std::swap(other.m_Size, m_Size);
        }

        //! Copies given array \p other to this array.
        ArrayAccessor& operator=(const ArrayAccessor& other)
        {
            Set(other);
            return *this;
        }

        //! Casts type to ConstArrayAccessor.
        operator ConstArrayAccessor<T, 3>() const
        {
            return ConstArrayAccessor<T, 3>(*this);
        }


    private:
        Dim3d m_Size;
        T* m_Data;
	};

    //! Type alias for 3-D array accessor.
    template <typename T> 
    using WriteAccessor3D = ArrayAccessor<T, 3>;


    template <typename T>
    class ConstArrayAccessor<T, 3> {
    public:
        //! Constructs empty 3-D read-only array accessor.
        ConstArrayAccessor(): m_Data{ nullptr }{}

        //! Constructs a read-only array accessor that wraps given array.
        //! \param size Size of the 3-D array.
        //! \param data Raw array pointer.
        ConstArrayAccessor(const Dim3d& size, const T* const data)
        {
            m_Size = size;
            m_Data = data;
        }

        //! Constructs a read-only array accessor that wraps given array.
        //! \param width Width of the 3-D array.
        //! \param height Height of the 3-D array.
        //! \param depth Depth of the 3-D array.
        //! \param data Raw array pointer.
        ConstArrayAccessor(
            size_t width, size_t height, size_t depth, const T* const data)
        {
            m_Size = { width, height, depth };
            m_Data = data;
        }

        //! Constructs a read-only array accessor from read/write accessor.
        explicit ConstArrayAccessor(const ArrayAccessor<T, 3>& other)
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

        //! Returns the const reference to the i-th element.
        const T& At(size_t i) const
        {
            ASSERT(i >= 0 && i < m_Size.m_Width* m_Size.m_Height* m_Size.m_Depth);
            return m_Data[i];
        }


        //! Returns the const reference to the element at (i, j, k).
        const T& At(size_t i, size_t j, size_t k) const
        {
            ASSERT(i >= 0 && i < m_Size.m_Width&&
                   j >= 0 && j < m_Size.m_Height&&
                   k >= 0 && k < m_Size.m_Depth);

            return m_Data[i + m_Size.m_Width * (j + m_Size.m_Height * k)];
        }

        //! Returns the begin iterator of the array.
        const T* const begin() const
        {
            return m_Data;
        }

        //! Returns the end iterator of the array.
        const T* const end() const
        {
            return m_Data + m_Size.m_Width * m_Size.m_Height * m_Size.m_Depth;
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
        const T* const Data() const
        {
            return m_Data;
        }


        template <typename Callback>
        void ForEach(Callback func) const
        {
            for (size_t k = 0; k < m_Size.m_Depth; ++k) {
                for (size_t j = 0; k < m_Size.m_Height; ++j) {
                    for (size_t i = 0; k < m_Size.m_Width; ++i)
                    {
                        func((*this)(i, j, k));
                    }
                }
            }
        }

        template <typename Callback>
        void ForEachIndex(Callback func) const
        {
            for (size_t k = 0; k < m_Size.m_Depth; ++k) {
                for (size_t j = 0; k < m_Size.m_Height; ++j) {
                    for (size_t i = 0; k < m_Size.m_Width; ++i)
                    {
                        func(i, j, k);
                    }
                }
            }
        }

        template <typename Callback>
        void ParallelForEach(Callback func) const
        {
            ParallelFor((size_t)0, m_Size.m_Width,
                (size_t)0, m_Size.m_Height,
                (size_t)0, m_Size.m_Depth,
                [&](size_t i, size_t j, size_t k)
                {
                    func((*this)(i, j, k));
                });
        }

        template <typename Callback>
        void ParallelForEachIndex(Callback func) const
        {
            ParallelFor((size_t)0, m_Size.m_Width,
                (size_t)0, m_Size.m_Height,
                (size_t)0, m_Size.m_Depth,
                func);
        }

        template <typename Callback>
        void ParallelForIndexRange(Callback func)const
        {
            ParallelRangeFor((size_t)0, m_Size.m_Width, (size_t)0, m_Size.m_Height, (size_t)0, m_Size.m_Depth, func);
        }


        //! Returns the linear index of the given =3-D coordinate (i, j, k).
        size_t Index(size_t i, size_t j, size_t k) const
        {
            return i + m_Size.m_Width * (j + m_Size.m_Height * k);
        }

        //! Returns the const reference to the i-th element.
        const T& operator[](size_t i) const
        {
            return m_Data[i];
        }

        //! Returns the reference to the element at (i, j, k).
        const T& operator()(size_t i, size_t j, size_t k) const
        {
            return m_Data[i + m_Size.m_Width * (j + m_Size.m_Height * k)];
        }


    private:
        Dim3d m_Size;
        const T* m_Data;
    };

    //! Type alias for 3-D const array accessor.
    template <typename T> 
    using ReadAccessor3D = ConstArrayAccessor<T, 3>;

}
