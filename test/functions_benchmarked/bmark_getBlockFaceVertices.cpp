#ifndef bmark_getBlockFaceVertices_cpp
#define bmark_getBlockFaceVertices_cpp

#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include "../../src/ecs/systems/blockRenderFunctions.cpp"

namespace kbmark {
namespace bmark_getBlockFaceVertices {


auto bma_a = glm::dvec3(2, 20, 20);
auto bma_b = glm::dvec3(0, 0, 0.5);

static void BM_getBlockFaceVertices_A(benchmark::State& state) {
  for (auto _ : state) {
    pce::brend::getBlockFaceVertices(bma_a, bma_b);
  }
}
BENCHMARK(BM_getBlockFaceVertices_A);

}
}
#endif /* bmark_getBlockFaceVertices_cpp */
