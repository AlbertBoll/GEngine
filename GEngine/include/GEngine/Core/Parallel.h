#pragma once
#include "tbb/tbb/parallel_for.h"
#include "tbb/tbb/parallel_reduce.h"
#include "tbb/tbb/blocked_range2d.h"
#include "tbb/tbb/blocked_range3d.h"



namespace GEngine
{


    template<typename T>
    struct RangeParams
    {
        T Start;
        T End;
        size_t Grainsize;
    };

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


    template <typename IndexType, typename Func, typename Partitioner = tbb::auto_partitioner>
    void ParallelRangeFor(
        const RangeParams<IndexType>& Range,
        const Func& function, const Partitioner& partitioner)
    {
        tbb::parallel_for(tbb::blocked_range<IndexType>(Range.Start, Range.End, Range.Grainsize),
            [&function](const tbb::blocked_range<IndexType>& range1d) {
                function(range1d.begin(), range1d.end());
            }, partitioner);

    }


    template <typename Res, typename IndexType, typename RealBodyFunc, typename ReductionFunc, typename Partitioner = tbb::auto_partitioner>
    Res ParallelReduce(
        const RangeParams<IndexType>& Range, Res initVal,
        const RealBodyFunc& realBody, const ReductionFunc& reduction ,const Partitioner& partitioner)
    {
        return tbb::parallel_reduce(tbb::blocked_range<IndexType>(Range.Start, Range.End, Range.Grainsize), initVal,
            [&realBody](const tbb::blocked_range<IndexType>& range1d, float local_res) {
                return realBody(range1d.begin(), range1d.end(), local_res);
            }, reduction, partitioner);

    }


    template <typename IndexType, typename Func, typename Partitioner = tbb::auto_partitioner>
    void ParallelRangeFor(
        const RangeParams<IndexType>& xRange,
        const RangeParams<IndexType>& yRange,
        const Func& function, const Partitioner& partitioner)
    {
        if (xRange.Start > xRange.End || yRange.Start > yRange.End) return;
        tbb::parallel_for(tbb::blocked_range2d<IndexType>(xRange.Start, xRange.End, xRange.Grainsize, yRange.Start, yRange.End, yRange.Grainsize),
            [&function](const tbb::blocked_range2d<IndexType>& range2d)
            {
                function(range2d.rows().begin(), range2d.rows().end(), range2d.cols().begin(), range2d.cols().end());
            }, partitioner);

    }

    template <typename IndexType, typename Func, typename Partitioner = tbb::auto_partitioner>
    void ParallelRangeFor(
        const RangeParams<IndexType>& xRange,
        const RangeParams<IndexType>& yRange,
        const RangeParams<IndexType>& zRange,
        const Func& function, const Partitioner& partitioner)
    {
        if (xRange.Start > xRange.End || yRange.Start > yRange.End || zRange.Start > zRange.End) return;
        tbb::parallel_for(tbb::blocked_range3d<IndexType>(xRange.Start, xRange.End, xRange.Grainsize, yRange.Start, yRange.End, yRange.Grainsize, zRange.Start, zRange.End, zRange.Grainsize),
            [&function](const tbb::blocked_range3d<IndexType>& range3d)
            {
                function(
                    range3d.rows().begin(),  range3d.rows().end(),
                    range3d.cols().begin(),  range3d.cols().end(),
                    range3d.pages().begin(), range3d.pages().end());
            }, partitioner);

    }
  

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
        tbb::parallel_for(tbb::blocked_range2d<IndexType>(beginIndexX, endIndexX, 64, beginIndexY, endIndexY, 64),
            [&function](const tbb::blocked_range2d<IndexType>& range2d)
            {
                function(range2d.rows().begin(), range2d.rows().end(), range2d.cols().begin(), range2d.cols().end());
            });

    }


    template<typename IndexType, typename Func>
    void ParallelRangeFor(IndexType beginIndexX, IndexType endIndexX, IndexType beginIndexY, IndexType endIndexY, IndexType beginIndexZ, IndexType endIndexZ, const Func& function)
    {

        if(beginIndexX > endIndexX || beginIndexY > endIndexY || beginIndexZ > endIndexZ) return;
        tbb::parallel_for(tbb::blocked_range3d<IndexType>(beginIndexX, endIndexX, beginIndexY, endIndexY, beginIndexZ, endIndexZ),
            [&function](const tbb::blocked_range3d<IndexType>& range3d)
            {
                function(
                         range3d.rows().begin(),  range3d.rows().end(),
                         range3d.cols().begin(),  range3d.cols().end(),
                         range3d.pages().begin(), range3d.pages().end());
            });
    }
}
