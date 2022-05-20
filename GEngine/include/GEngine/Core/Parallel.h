#pragma once
#include "tbb/tbb.h"


namespace GEngine
{

    enum class ExecutionPolicy { Serial, Parallel };

    template <typename IndexType, typename Func>
    void ParallelFor(IndexType beginIndex, IndexType endIndex,
        const Func& function,
        ExecutionPolicy policy = ExecutionPolicy::Parallel);

    template <typename IndexType, typename Func>
    void ParallelFor(IndexType beginIndexX, IndexType endIndexX,
        IndexType beginIndexY, IndexType endIndexY,
        const Func& function,
        ExecutionPolicy policy = ExecutionPolicy::Parallel);


    template <typename IndexType, typename Func>
    void ParallelFor(IndexType beginIndexX, IndexType endIndexX,
        IndexType beginIndexY, IndexType endIndexY,
        IndexType beginIndexZ, IndexType endIndexZ,
        const Func& function,
        ExecutionPolicy policy = ExecutionPolicy::Parallel);

  

    template<typename IndexType, typename Func>
    void ParallelFor(IndexType beginIndex, IndexType endIndex, const Func& function, ExecutionPolicy policy)
    {
        if (beginIndex > endIndex) return;
        
        if (policy == ExecutionPolicy::Parallel)
        {
            tbb::parallel_for(beginIndex, endIndex, function);
        }

        else
        {
            for (size_t i = beginIndex; i < endIndex; ++i) {
                function(i);
            }
        }

    }


    template<typename IndexType, typename Func>
    void ParallelFor(IndexType beginIndexX, IndexType endIndexX, IndexType beginIndexY, IndexType endIndexY, const Func& function, ExecutionPolicy policy)
    {
        ParallelFor(beginIndexY, endIndexY,
            [&](IndexType j) {
                for (IndexType i = beginIndexX; i < endIndexX; ++i) {
                    function(i, j);
                }
            },
            policy);
    }



    template<typename IndexType, typename Func>
    void ParallelFor(IndexType beginIndexX, IndexType endIndexX, IndexType beginIndexY, IndexType endIndexY, IndexType beginIndexZ, IndexType endIndexZ, const Func& function, ExecutionPolicy policy)
    {
        ParallelFor(beginIndexZ, endIndexZ,
            [&](IndexType k) {
                for (IndexType j = beginIndexY; j < endIndexY; ++j) {
                    for (IndexType i = beginIndexX; i < endIndexX; ++i) {
                        function(i, j, k);
                    }
                }
            },
            policy);
    }
}
