#include <benchmark/benchmark.h>

#include "addTwo1.cpp"
#include "addTwo2.cpp"

extern std::vector<struct ListNode*> test_cases;

static void BM_addTwo1(benchmark::State& state) {
    Solution1 sol;
    int idx1 = state.range(0);
    int idx2 = state.range(1);
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
    int idx2 = state.range(1);
    ListNode* l1 = test_cases[idx1];
    ListNode* l2 = test_cases[idx2];
    for ( auto _ : state ) {
         ListNode* sum = sol.addTwoNumbers(l1, l2);
         benchmark::DoNotOptimize(sum);
    }
}

static void RegisterBenchmarks() {
    for (size_t i = 0; i < test_cases.size(); ++i) {
        for (size_t j = 0; j < test_cases.size(); ++j) {
            benchmark::RegisterBenchmark("BM_addTwo1", BM_addTwo1)->Args({static_cast<int>(i), static_cast<int>(j)});
        }
    }
    for (size_t i = 0; i < test_cases.size(); ++i) {
        for (size_t j = 0; j < test_cases.size(); ++j) {
            benchmark::RegisterBenchmark("BM_addTwo2", BM_addTwo2)->Args({static_cast<int>(i), static_cast<int>(j)});
        }
    }
}

int main(int argc, char** argv) {
    RegisterBenchmarks();
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
    return 0;
}
