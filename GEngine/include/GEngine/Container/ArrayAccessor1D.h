#pragma once
#include"Array.h"
#include"Core/Assert.h"
#include"Core/Parallel.h"



namespace GEngine::GridBasedContainer
{
    template <typename T>
    class ArrayAccessor<T, 1> final {

    public:
        //! Constructs empty 1-D array accessor.
        ArrayAccessor(): m_Size(0), m_Data(nullptr) {};

        //! Constructs an array accessor that wraps given array.
        ArrayAccessor(size_t size, T* const data);

        //! Copy constructor.
        ArrayAccessor(const ArrayAccessor& other);

        //! Copies given array accessor \p other.
        ArrayAccessor& operator=(const ArrayAccessor& other);

        //! Casts type to ConstArrayAccessor.
        operator ConstArrayAccessor<T, 1>() const;

        //! Replaces the content with given \p other array accessor.
        void Set(const ArrayAccessor& other);

        //! Resets the array.
        void Reset(std::size_t size, T* const data);

        //! Returns the reference to the i-th element.
        T& At(size_t i);

        //! Returns the const reference to the i-th element.
        const T& At(size_t i) const;

        //! Returns the begin iterator of the array.
        T* const begin() const;

        //! Returns the end iterator of the array.
        T* const end() const;

        //! Returns the begin iterator of the array.
        T* begin();

        //! Returns the end iterator of the array.
        T* end();

        //! Returns size of the array.
        size_t Size() const;

        //! Returns the raw pointer to the array data.
        T* const Data() const;

        //! Swaps the content of with \p other array accessor.
        void Swap(ArrayAccessor& other);

        template <typename Callback>
        void ForEach(Callback func);

        template <typename Callback>
        void ForEachIndex(Callback func);

        template <typename Callback>
        void ParallelForEach(Callback func);

        template <typename Callback>
        void ParallelForEachIndex(Callback func);

        template <typename Callback>
        void ParallelForIndexRange(Callback func);

        template <typename Callback, typename Partitioner = tbb::auto_partitioner>
        void ParallelForIndexRange(const RangeParams<size_t>& range, Callback func, const Partitioner& partitioner = tbb::auto_partitioner{});

       


       //template <typename Callback>
       //void ForEach(Callback func) const;

       //template <typename Callback>
       //void ForEachIndex(Callback func) const;

        //template <typename Callback>
        //void ParallelForEach(Callback func) const;

        //template <typename Callback>
        //void ParallelForEachIndex(Callback func) const;


        //! Returns the reference to i-th element.
        T& operator[](size_t i);

        //! Returns the const reference to i-th element.
        const T& operator[](size_t i) const;

    private:
        std::size_t m_Size;
        T* m_Data;
    };


    template <typename T> 
    using WriteAccessor1D = ArrayAccessor<T, 1>;


    template <typename T>
    class ConstArrayAccessor<T, 1> {
    public:
        //! Constructs empty 1-D array accessor.
        ConstArrayAccessor(): m_Size(0), m_Data(nullptr) {};

        //! Constructs an read-only array accessor that wraps given array.
        ConstArrayAccessor(size_t size, const T* const data) {
            m_Size = size;
            m_Data = data;
        };

        //! Constructs a read-only array accessor from read/write accessor.
        explicit ConstArrayAccessor(const ArrayAccessor<T, 1>& other)
        {
            m_Size = other.m_Size;
            m_Data = other.m_Data;
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
            ASSERT(i >= 0 && i < m_Size);
            return m_Data[i];
        }

        //! Returns the begin iterator of the array.
        const T* const begin() const
        {
            return m_Data;
        }

        //! Returns the end iterator of the array.
        const T* const end() const
        {
            return m_Data + m_Size;
        }

        //! Returns size of the array.
        size_t Size() const
        {
            return m_Size;
        }

        //! Returns the raw pointer to the array data.
        const T* const Data() const
        {
            return m_Data;
        }

        //!
        //! \brief Iterates the array and invoke given \p func for each element.
        //!
        //! This function iterates the array elements and invoke the callback
        //! function \p func. The callback function takes array's element as its
        //! input. The order of execution will be 0 to N-1 where N is the size of
        //! the array. Below is the sample usage:
        //!
        //! \code{.cpp}
        //! int data = {1, 2, 3, 4, 5, 6};
        //! ConstArrayAccessor<int, 1> acc(6, data);
        //! acc.forEach([](int elem) {
        //!     printf("%d\n", elem);
        //! });
        //! \endcode
        //!
        template <typename Callback>
        void ForEach(Callback func) const
        {
            for (size_t i = 0; i < m_Size; ++i) {
                func((*this)[i]);
            }
        }

        //!
        //! \brief Iterates the array and invoke given \p func for each index.
        //!
        //! This function iterates the array elements and invoke the callback
        //! function \p func. The callback function takes one parameter which is the
        //! index of the array. The order of execution will be 0 to N-1 where N is
        //! the size of the array. Below is the sample usage:
        //!
        //! \code{.cpp}
        //! int data = {1, 2, 3, 4, 5, 6};
        //! ConstArrayAccessor<int, 1> acc(6, data);
        //! acc.forEachIndex([&](size_t i) {
        //!     data[i] = acc[i] * acc[i];
        //! });
        //! \endcode
        //!
        template <typename Callback>
        void ForEachIndex(Callback func) const
        {
            for (size_t i = 0; i < m_Size; ++i) {
                func(i);
            }
        }

       
        //! \brief Iterates the array and invoke given \p func for each index in
        //!     parallel using multi-threading.
        //!
        //! This function iterates the array elements and invoke the callback
        //! function \p func in parallel using multi-threading. The callback
        //! function takes one parameter which is the index of the array. The order
        //! of execution will be non-deterministic since it runs in parallel.
        //! Below is the sample usage:
        //!
   
        template <typename Callback>
        void ParallelForEachIndex(Callback func) const
        {
            ParallelFor((size_t)0, m_Size, func);
        }

        template <typename Callback>
        void ParallelForEach(Callback func) const
        {
            ParallelFor((std::size_t)0, m_Size, [&](size_t i) {
                func((*this)[i]);
                }
            );
        }

        template <typename Callback>
        void ParallelForIndexRange(Callback func)const
        {
            ParallelRangeFor((size_t)0, m_Size, func);
        }

        template <typename Callback, typename Partitioner = tbb::auto_partitioner>
        void ParallelForIndexRange(const RangeParams<size_t>& range, Callback func, const Partitioner& partitioner = tbb::auto_partitioner{}) const;

        template <typename RealBodyFunc, typename ReductionFunc, typename Partitioner = tbb::auto_partitioner>
        T ParallelReduce_(const RangeParams<size_t>& range, T initVal, const RealBodyFunc& realBody, const ReductionFunc& reduction, const Partitioner& partitioner = tbb::auto_partitioner{})const;

        //! Returns the const reference to i-th element.
        const T& operator[](size_t i) const
        {
            ASSERT(i >= 0 && i < m_Size);
            return m_Data[i];
        }

    private:
        size_t m_Size;
        const T* m_Data;
    };

    //! Type alias for 1-D const array accessor.
    template <typename T> 
    using ReadAccessor1D = ConstArrayAccessor<T, 1>;



    template<typename T>
    inline ArrayAccessor<T, 1>::ArrayAccessor(std::size_t size, T* const data)
    {
        Reset(size, data);
    }

    template<typename T>
    inline ArrayAccessor<T, 1>::ArrayAccessor(const ArrayAccessor& other)
    {
        Set(other);
    }

    template<typename T>
    inline ArrayAccessor<T, 1>& ArrayAccessor<T, 1>::operator=(const ArrayAccessor& other)
    {
        Set(other);
        return *this;
    }

    template<typename T>
    inline ArrayAccessor<T, 1>::operator ConstArrayAccessor<T, 1>() const
    {
        return ConstArrayAccessor<T, 1>(*this);
    }

   

    template<typename T>
    inline void ArrayAccessor<T, 1>::Set(const ArrayAccessor& other)
    {
        Reset(other.m_Size, other.m_Data);
    }

    template<typename T>
    inline void ArrayAccessor<T, 1>::Reset(std::size_t size, T* const data)
    {
        m_Size = size;
        m_Data = data;

    }

    template<typename T>
    inline T& ArrayAccessor<T, 1>::At(std::size_t i)
    {
        ASSERT(i >= 0 && i < m_Size);
        return m_Data[i];
    }

    template<typename T>
    inline const T& ArrayAccessor<T, 1>::At(std::size_t i) const
    {
        ASSERT(i >= 0 && i < m_Size);
        return m_Data[i];
    }

    template<typename T>
    inline T* const ArrayAccessor<T, 1>::begin() const
    {
        return m_Data;
    }

    template<typename T>
    inline T* const ArrayAccessor<T, 1>::end() const
    {
        return m_Data + m_Size;
    }

    template<typename T>
    inline T* ArrayAccessor<T, 1>::begin()
    {
        return m_Data;
    }

    template<typename T>
    inline T* ArrayAccessor<T, 1>::end()
    {
        return m_Data + m_Size;
    }

    template<typename T>
    inline std::size_t ArrayAccessor<T, 1>::Size() const
    {
        return m_Size;
    }

    template<typename T>
    inline T* const ArrayAccessor<T, 1>::Data() const
    {
        return m_Data;
    }


    template<typename T>
    inline void ArrayAccessor<T, 1>::Swap(ArrayAccessor& other)
    {
        std::swap(other.m_Data, m_Data);
        std::swap(other.m_Size, m_Size);
    }

    template<typename T>
    inline T& ArrayAccessor<T, 1>::operator[](std::size_t i)
    {
        ASSERT(i >= 0 && i < m_Size);
        return m_Data[i];
    }

    template<typename T>
    inline const T& ArrayAccessor<T, 1>::operator[](std::size_t i) const
    {
        ASSERT(i >= 0 && i < m_Size);
        return m_Data[i];
    }


    template<typename T>
    template<typename Callback>
    inline void ArrayAccessor<T, 1>::ForEach(Callback func)
    {
        for (size_t i = 0; i < m_Size; ++i) {
            func((*this)[i]);
        }
    }


    template<typename T>
    template<typename Callback>
    inline void ArrayAccessor<T, 1>::ForEachIndex(Callback func)
    {
        for (size_t i = 0; i < m_Size; ++i) {
            func(i);
        }
    }

    template<typename T>
    template<typename Callback>
    inline void ArrayAccessor<T, 1>::ParallelForEach(Callback func)
    {
        ParallelFor((size_t)0, m_Size, [&](size_t i) {
            func((*this)[i]);
            }
        );
    }


    template<typename T>
    template<typename Callback>
    inline void ArrayAccessor<T, 1>::ParallelForEachIndex(Callback func)
    {
        ParallelFor((size_t)0, m_Size, func);
    }

    template<typename T>
    template<typename Callback>
    inline void ArrayAccessor<T, 1>::ParallelForIndexRange(Callback func)
    {
        ParallelRangeFor((size_t)0, m_Size, func);
    }

#if 0
    /*  template<typename T>
  template<typename Callback>
  inline void ArrayAccessor<T, 1>::ForEach(Callback func) const
  {
      for (size_t i = 0; i < m_Size; ++i) {
          func(At(i));
      }
  }*/

  /* template<typename T>
    template<typename Callback>
    inline void ArrayAccessor<T, 1>::ForEachIndex(Callback func) const
    {
        for (size_t i = 0; i < m_Size; ++i) {
            func(i);
    }
  }*/

  /*   template<typename T>
  template<typename Callback>
  inline void ArrayAccessor<T, 1>::ParallelForEach(Callback func) const
  {
      ParallelFor((std::size_t)0, m_Size, [&](size_t i) {
          func(At(i));
          }
      );
  }*/

  /* template<typename T>
     template<typename Callback>
     inline void ArrayAccessor<T, 1>::ParallelForEachIndex(Callback func) const
     {
         ParallelFor((size_t)0, m_Size, func);
     }
  */

#endif

    template<typename T>
    template<typename Callback, typename Partitioner>
    inline void ArrayAccessor<T, 1>::ParallelForIndexRange(const RangeParams<size_t>& range, Callback func, const Partitioner& partitioner)
    {
        ParallelRangeFor(range, func, partitioner);
    }



    template<typename T>
    template<typename Callback, typename Partitioner>
    inline void ConstArrayAccessor<T, 1>::ParallelForIndexRange(const RangeParams<size_t>& range, Callback func, const Partitioner& partitioner) const
    {
        ParallelRangeFor(range, func, partitioner);
    }

    template<typename T>
    template<typename RealBodyFunc, typename ReductionFunc, typename Partitioner>
    inline T ConstArrayAccessor<T, 1>::ParallelReduce_(const RangeParams<size_t>& range, T initVal, const RealBodyFunc& realBody, const ReductionFunc& reduction, const Partitioner& partitioner) const
    {
        return ParallelReduce(range, initVal, realBody, reduction, partitioner);
    }

}
