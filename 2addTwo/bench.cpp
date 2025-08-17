#include <benchmark/benchmark.h>

#include "addTwo1.cpp"
#include "addTwo2.cpp"

extern std::vector<std::pair<ListNode*, ListNode*>> test_cases;

static void BM_addTwo1(benchmark::State& state) {
    Solution1 sol;
    int idx = state.range(0);
    auto [l1, l2] = test_cases[idx];
    for (auto _ : state) {
         ListNode* sum = sol.addTwoNumbers(l1, l2);
         benchmark::DoNotOptimize(sum);
    }
}

static void BM_addTwo2(benchmark::State& state) {
    Solution2 sol;
    int idx = state.range(0);
    auto [l1, l2] = test_cases[idx];
    for ( auto _ : state ) {
         ListNode* sum = sol.addTwoNumbers(l1, l2);
         benchmark::DoNotOptimize(sum);
    }
}

int main(int argc, char** argv) {
    // Register benchmarks after test_cases is initialized
    if (!test_cases.empty()) {
        benchmark::RegisterBenchmark("BM_addTwo1", BM_addTwo1)->DenseRange(0, test_cases.size() - 1);
        benchmark::RegisterBenchmark("BM_addTwo2", BM_addTwo2)->DenseRange(0, test_cases.size() - 1);
    }

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
    return 0;
}
