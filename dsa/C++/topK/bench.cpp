#include <benchmark/benchmark.hpp>

#include "topK.hpp"

std::vector<std::vector<int>> testCases = { /* TODO */ };

constexpr std::size_t K_SIZE = 5;

static void BM_topK_insertionSort(benchmark::State& state)
{
   TopK topk<int, K_SIZE>; // std::greater default is fine
   int idx = state.range(0);
   auto testVec = testCases[idx];

   for ( auto _ : state )
   {
      topk.pass(testVec);
      auto topElements = topk.topK();
      benchmark::DoNotOptimize(topElements);
   }
}
BENCHMARK(BM_topK_InsertionSort)->DenseRange(0, testCases.size() - 1);

//static void BM_topK_mergeSort(benchmark::State& state)
//{
//   TopKMergeSort topk<int, K_SIZE>; // std::greater default is fine
//   int idx = state.range(0);
//   auto testVec = testCases[idx];
//
//   for ( auto _ : state )
//   {
//      topk.pass(testVec);
//      auto topElements = topk.topK();
//      benchmark::DoNotOptimize(topElements);
//   }
//}

BENCHMARK_MAIN();
