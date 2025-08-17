#include <benchmark/benchmark.h>

#include "maxProdSubSeq.cpp"

using namespace std;

extern vector<pair<vector<int>,int>> testCases;

static void BM_maxProd1( benchmark::State& state ) {
    auto [nums, m] = testCases[ state.range(0) ];
    for ( auto _ : state ) {
        Solution1 sol;
        long long result = sol.maximumProduct(nums, m);
        benchmark::DoNotOptimize(result);
    }
}

int main(int argc, char * argv[]) {
    if ( !testCases.empty() ) {
        benchmark::RegisterBenchmark("BM_maxProd1", BM_maxProd1)->DenseRange(0, testCases.size() - 1);
    }

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();

    return 0;
}
