#include <benchmark/benchmark.h>

#include "addTwoNumbers.cpp"
#include "addtwo.cpp"

static ListNode n6 = { 0, nullptr };
static ListNode n5 = { 3, &n6     };
static ListNode n4 = { 1, &n5     };
static ListNode n3 = { 0, &n4     };
static ListNode n2 = { 9, &n3     };
static ListNode n1 = { 5, &n2     };
static ListNode l1 = n1;

static ListNode m6 = { 9, nullptr };
static ListNode m5 = { 9, &m6     };
static ListNode m4 = { 9, &m5     };
static ListNode m3 = { 9, &m4     };
static ListNode m2 = { 9, &m3     };
static ListNode m1 = { 9, &m2     };
static ListNode l2 = m1;

static void BM_AddTwo_Sol1(benchmark::State& state) {
   Solution1 sol;
   for ( auto _ : state ) {
      benchmark::DoNotOptimize(l1);
      benchmark::DoNotOptimize(l2);
      ListNode* sum = sol.addTwoNumbers(&l1, &l2);
      benchmark::DoNotOptimize(sum);
   }
}

static void BM_AddTwo_Sol2(benchmark::State& state) {
   Solution2 sol;
   for ( auto _ : state ) {
      benchmark::DoNotOptimize(l1);
      benchmark::DoNotOptimize(l2);
      ListNode* sum = sol.addTwoNumbers(&l1, &l2);
      benchmark::DoNotOptimize(sum);
   }
}


BENCHMARK(BM_AddTwo_Sol1);
BENCHMARK(BM_AddTwo_Sol2);
BENCHMARK_MAIN();
