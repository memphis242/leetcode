#include <benchmark/benchmark.h>

#include "twosum1.cpp"
#include "twosum2.cpp"
#include "twosum3.cpp"

static const std::vector< std::pair< std::vector<int>, int > > test_cases =
{
    { {2, 7, 11, 15}, 9 },
    { {3, 2, 4}, 6 },
    { {3, 3}, 6 },
    { {1, 5, 3, 7}, 8 },
    { {0, 4, 3, 0}, 0 },
    { {-1, -2, -3, -4, -5}, -8 },
    { {1, 2, 3, 4, 5}, 9 },
    { {10, 20, 10, 40, 50, 60, 70}, 50 },
    { {1, 2}, 3 },
    { {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 19 },
    { {100, 200, 300, 400}, 700 },
    { {5, 75, 25}, 100 },
    { {2, 4, 6, 8, 10}, 12 },
    { {1, 1, 1, 2, 3}, 4 },
    { {-10, 20, 10, -20, 30}, 0 },
    { {0, 1, 2, 3, 4, 5}, 5 },
    { {1, 3, 5, 7, 9}, 10 },
    { {2, 2, 2, 2}, 4 },
    { {-3, 4, 3, 90}, 0 },
    { {1, 2, 5, 6},  7}
};

static void BM_TwoSum1(benchmark::State& state) {
    const auto& [nums, target] = test_cases[state.range(0)];
    for ( auto _ : state ) {
        Solution1 sol;
        auto result = sol.twoSum(nums, target);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_TwoSum1)->DenseRange(0, test_cases.size() - 1);

static void BM_TwoSum2(benchmark::State& state) {
    const auto& [nums, target] = test_cases[state.range(0)];
    for ( auto _ : state ) {
        Solution2 sol;
        auto result = sol.twoSum(nums, target);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_TwoSum2)->DenseRange(0, test_cases.size() - 1);

static void BM_TwoSum3(benchmark::State& state) {
    const auto& [nums, target] = test_cases[state.range(0)];
    for ( auto _ : state ) {
        Solution3 sol;
        auto result = sol.twoSum(nums, target);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_TwoSum3)->DenseRange(0, test_cases.size() - 1);

BENCHMARK_MAIN();
