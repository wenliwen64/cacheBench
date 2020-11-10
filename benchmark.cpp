#include <benchmark/benchmark.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include <random>
#include <cstdint>

using namespace std;

template<typename T>
static T rng(T const low, T const high) {
    static std::random_device r;
    static std::default_random_engine e(r());

    std::uniform_int_distribution<T> rng(low, high);
    return rng(e); 
}

static void BM_VectorAccess(benchmark::State& state) {
    size_t cacheSizeGuess = state.range(0) * 1024; /* in kBytes */
    size_t vecSize = cacheSizeGuess / 4 / 2; /* # of int32_t in each vector */
    vector<size_t> indices(vecSize); 
    vector<int32_t> numbers(vecSize); 
    for (auto& k : numbers) 
        k = rng<int32_t>(0, vecSize - 1);
    for (auto& k : indices)
        k = rng<size_t>(0, vecSize - 1);

    for (auto _ : state) {
        long sum = 0;
        for (auto const& idx : indices) {
            sum += numbers[idx];
            benchmark::DoNotOptimize(sum);
        }
    }

    state.SetBytesProcessed(long(state.iterations()) * cacheSizeGuess);
    state.SetLabel(to_string(state.range(0))+ "K");
}

BENCHMARK(BM_VectorAccess)->RangeMultiplier(2)->Range(1, 1024);
BENCHMARK_MAIN();