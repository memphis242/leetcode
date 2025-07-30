#include <benchmark/benchmark.h>
#include "fizbuz.hpp"

static void BM_FizBuzMap(benchmark::State& state)
{
   std::string outstr;
   for ( auto _ : state )
   {
      (void)fizbuz_map();
   }
}

static void BM_FizBuzNaive(benchmark::State& state)
{
   std::string outstr;
   for ( auto _ : state )
   {
      (void)fizbuz_naive();
   }
}

BENCHMARK(BM_FizBuzMap);
BENCHMARK(BM_FizBuzNaive);

BENCHMARK_MAIN();
