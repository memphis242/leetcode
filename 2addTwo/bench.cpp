#include <random>

#include <benchmark/benchmark.h>

#include "addTwo1.cpp"
#include "addTwo2.cpp"

extern std::vector<struct ListNode*> test_cases;

static void BM_addTwo1(benchmark::State& state) {
    Solution1 sol;
    int idx1 = state.range(0);
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(0, test_cases.size() - 1); // Define the range
    int idx2 = distr(gen); // idx2 will be a random idx to pair with idx1
    ListNode* l1 = test_cases[idx1];
    ListNode* l2 = test_cases[idx2];
    for (auto _ : state) {
         ListNode* sum = sol.addTwoNumbers(l1, l2);
         benchmark::DoNotOptimize(sum);
    }
}

static void BM_addTwo2(benchmark::State& state) {
    Solution2 sol;
    int idx1 = state.range(0);
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(0, test_cases.size() - 1); // Define the range
    int idx2 = distr(gen); // idx2 will be a random idx to pair with idx1
    ListNode* l1 = test_cases[idx1];
    ListNode* l2 = test_cases[idx2];
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
