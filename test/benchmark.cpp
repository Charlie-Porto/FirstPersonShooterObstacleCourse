#ifndef main_cpp
#define main_cpp

#include <vector>
#include <benchmark/benchmark.h>
#include <ezprint.cpp>

#include "functions_benchmarked/bmark_convertPointOnViewSphereToPixel.cpp"
#include "functions_benchmarked/bmark_fastconvertPointOnViewSphereToPixel.cpp"

// static void BM_test_funcA(benchmark::State& state) {
//   for (auto _ : state) {
//     ;
//   }
// }

// static void BM_test_funcB(benchmark::State& state) {
//   for (auto _ : state) {
//     std::vector<int> a(30);
//   }
// }
// BENCHMARK(BM_test_funcA)->Args({2000});

BENCHMARK_MAIN();










#endif /* main_cpp */
