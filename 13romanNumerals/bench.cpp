#include <benchmark/benchmark.h>

#include <array>

#include "romanNumerals.cpp"

static const array<string, 20> testcases =
{
    "MMMCMXCIX",      // 3999 (max standard Roman numeral)
    "MMMDCCCLXXXVIII",// 3888
    "MCDXLIV",        // 1444
    "MMXXIV",         // 2024
    "CDXLIV",         // 444
    "I",              // 1 (simple)
    "II",             // 2 (simple)
    "III",            // 3 (simple)
    "IV",             // 4 (simple)
    "V",              // 5 (simple)
    "MDCLXVI",        // 1666
    "MMMDCCXXIV",     // 3724
    "MMMDCCCLXXXIX",  // 3889
    "MCMXCIV",        // 1994
    "MMMDCCCLXXXVII", // 3887
    "MMMDCCCLXXXVI",  // 3886
    "MMMDCCCLXXXV",   // 3885
    "MMMDCCCLXXXIV",  // 3884
    "MMMDCCCLXXXIII", // 3883
    "MMMDCCCLXXXII"   // 3882
};

static void BM_romanNumerals1(benchmark::State& state) {
    string test = testcases[state.range(0)];
    for ( auto _ : state ) {
        Solution sol;
        int result = sol.romanToInt(test);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_romanNumerals1)->DenseRange(0, testcases.size() - 1);

BENCHMARK_MAIN();
