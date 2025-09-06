#include <benchmark/benchmark.h>

#include "topK.hpp"

extern std::vector<std::vector<int>> testcases;

constexpr std::size_t K_SIZE = 5;

static void BM_topK_insertionSort(benchmark::State& state)
{
   TopK<int, K_SIZE> topk; // std::greater default is fine
   int idx = state.range(0);
   auto testvec = testcases[idx];

   for ( auto _ : state )
   {
      topk.pass(testvec);
      auto topElements = topk.topK();
      benchmark::DoNotOptimize(topElements);
   }
}

//static void BM_topK_mergeSort(benchmark::State& state)
//{
//   TopKMergeSort topk<int, K_SIZE>; // std::greater default is fine
//   int idx = state.range(0);
//   auto testVec = testcases[idx];
//
//   for ( auto _ : state )
//   {
//      topk.pass(testVec);
//      auto topElements = topk.topK();
//      benchmark::DoNotOptimize(topElements);
//   }
//}

int main(int argc, char **argv)
{
   // Register benchmarks after testcases is initialized
   if (!testcases.empty())
   {
      benchmark::RegisterBenchmark("TopK Insertion Sort", BM_topK_insertionSort)->DenseRange(0, testcases.size()-1);
      //benchmark::RegisterBenchmark("TopK Merge Sort", BM_topK_mergeSort)->DenseRange(0, testcases.size()-1);
   }
   else
      return 1; // Empty testcases!

   benchmark::Initialize(&argc, argv);
   benchmark::RunSpecifiedBenchmarks();
   benchmark::Shutdown();

   return 0;
}
