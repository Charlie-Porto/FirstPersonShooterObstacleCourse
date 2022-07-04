#ifndef bmark_fastconvertPointOnViewSphereToPixel_cpp
#define bmark_fastconvertPointOnViewSphereToPixel_cpp

#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include "../../src/ecs/systems/subsystems/spacePixelConversionFunctions.cpp"

namespace kbmark {
namespace bmark_fastconvertPointOnViewSphereToPixel {


auto bma_a = glm::dvec3(.01, .01, .01);
auto bma_b = glm::dvec3(0, 0, 0);
static void BM_fastconvertPointOnViewSphereToPixel_A(benchmark::State& state) {
  for (auto _ : state) {
    pce::pix_map::fastconvertPointOnViewSphereToPixel(bma_a, bma_b);
  }
}
BENCHMARK(BM_fastconvertPointOnViewSphereToPixel_A);

auto bmb_a = glm::dvec3(.1, .1, .1);
auto bmb_b = glm::dvec3(0, 0, 0);
static void BM_fastconvertPointOnViewSphereToPixel_B(benchmark::State& state) {
  for (auto _ : state) {
    pce::pix_map::fastconvertPointOnViewSphereToPixel(bmb_a, bmb_b);
  }
}
BENCHMARK(BM_fastconvertPointOnViewSphereToPixel_B);
}

auto bmc_a = glm::dvec3(.12932, .120994, .924);
auto bmc_b = glm::dvec3(0, 0, 0);
static void BM_fastconvertPointOnViewSphereToPixel_C(benchmark::State& state) {
  for (auto _ : state) {
    pce::pix_map::fastconvertPointOnViewSphereToPixel(bmc_a, bmc_b);
  }
}
BENCHMARK(BM_fastconvertPointOnViewSphereToPixel_C);

auto bmd_a = glm::dvec3(.6032, .40403, .304);
auto bmd_b = glm::dvec3(0, 0, 0);
static void BM_fastconvertPointOnViewSphereToPixel_D(benchmark::State& state) {
  for (auto _ : state) {
    pce::pix_map::fastconvertPointOnViewSphereToPixel(bmd_a, bmd_b);
  }
}
BENCHMARK(BM_fastconvertPointOnViewSphereToPixel_D);
}
#endif /* bmark_fastconvertPointOnViewSphereToPixel_cpp */
