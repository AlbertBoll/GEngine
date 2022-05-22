#pragma once
#include "tbb/tbb/parallel_for.h"
#include "tbb/tbb/blocked_range2d.h"
#include "tbb/tbb/blocked_range3d.h"

namespace GEngine
{

    enum class ExecutionPolicy { Serial, Parallel };

    template <typename IndexType, typename Func>
    void ParallelFor(IndexType beginIndex, IndexType endIndex,
        const Func& function);

    template <typename IndexType, typename Func>
    void ParallelRangeFor(
        IndexType beginIndex, IndexType endIndex,
        const Func& function);

    template <typename IndexType, typename Func>
    void ParallelFor(
        IndexType beginIndexX, IndexType endIndexX,
        IndexType beginIndexY, IndexType endIndexY,
        const Func& function);

    template <typename IndexType, typename Func>
    void ParallelRangeFor(
        IndexType beginIndexX, IndexType endIndexX,
        IndexType beginIndexY, IndexType endIndexY,
        const Func& function);


    template <typename IndexType, typename Func>
    void ParallelFor(
        IndexType beginIndexX, IndexType endIndexX,
        IndexType beginIndexY, IndexType endIndexY,
        IndexType beginIndexZ, IndexType endIndexZ,
        const Func& function);

    template <typename IndexType, typename Func>
    void ParallelRangeFor(
        IndexType beginIndexX, IndexType endIndexX,
        IndexType beginIndexY, IndexType endIndexY,
        IndexType beginIndexZ, IndexType endIndexZ,
        const Func& function);

  

    template<typename IndexType, typename Func>
    void ParallelFor(IndexType beginIndex, IndexType endIndex, const Func& function)
    {
        if (beginIndex > endIndex) return;
        
      
        tbb::parallel_for(beginIndex, endIndex, function);            

    }

 

    template<typename IndexType, typename Func>
    void ParallelFor(IndexType beginIndexX, IndexType endIndexX, IndexType beginIndexY, IndexType endIndexY, const Func& function)
    {
        ParallelFor(beginIndexY, endIndexY,
            [&](IndexType j) {
                for (IndexType i = beginIndexX; i < endIndexX; ++i) {
                    function(i, j);
                }
            });
    }

    template<typename IndexType, typename Func>
    void ParallelFor(IndexType beginIndexX, IndexType endIndexX, IndexType beginIndexY, IndexType endIndexY, IndexType beginIndexZ, IndexType endIndexZ, const Func& function)
    {
        ParallelFor(beginIndexZ, endIndexZ,
            [&](IndexType k) {
                for (IndexType j = beginIndexY; j < endIndexY; ++j) {
                    for (IndexType i = beginIndexX; i < endIndexX; ++i) {
                        function(i, j, k);
                    }
                }
            });
    }


    template<typename IndexType, typename Func>
    void ParallelRangeFor(IndexType beginIndex, IndexType endIndex, const Func& function)
    {
        if (beginIndex > endIndex) return;

        tbb::parallel_for(tbb::blocked_range<IndexType>(beginIndex, endIndex),
            [&function](const tbb::blocked_range<IndexType>& range1d) {
                function(range1d.begin(), range1d.end());
            });

    }


    template<typename IndexType, typename Func>
    void ParallelRangeFor(IndexType beginIndexX, IndexType endIndexX, IndexType beginIndexY, IndexType endIndexY, const Func& function)
    {
        if (beginIndexX > endIndexX || beginIndexY > endIndexY) return;
        tbb::parallel_for(tbb::blocked_range2d<IndexType>(beginIndexX, endIndexX, beginIndexY, endIndexY),
            [&function](const tbb::blocked_range2d<IndexType>& range2d)
            {
                function(range2d.cols().begin(), range2d.cols().end(), range2d.rows().begin(), range2d.rows().end());
            });

    }


    template<typename IndexType, typename Func>
    void ParallelRangeFor(IndexType beginIndexX, IndexType endIndexX, IndexType beginIndexY, IndexType endIndexY, IndexType beginIndexZ, IndexType endIndexZ, const Func& function)
    {

        if(beginIndexX > endIndexX || beginIndexY > endIndexY || beginIndexZ > endIndexZ) return;
        tbb::parallel_for(tbb::blocked_range3d<IndexType>(beginIndexX, endIndexX, beginIndexY, endIndexY, beginIndexZ, endIndexZ),
            [&function](const tbb::blocked_range3d<IndexType>& range3d)
            {
                function(range3d.cols().begin(),  range3d.cols().end(),
                         range3d.rows().begin(),  range3d.rows().end(),
                         range3d.pages().begin(), range3d.pages().end());
            });
    }
}
