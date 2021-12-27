#include <benchmark/benchmark.h>  // Google benchmark

#include <minimgprc/minimgprc.h>
#include <minimgapi/imgguard.hpp>

void Benchmark(benchmark::State& state, MinTyp type, int channels) {
  DECLARE_GUARDED_MINIMG(src);
  DECLARE_GUARDED_MINIMG(dst);

  int width = static_cast<int>(state.range(0));
  int height = static_cast<int>(state.range(1));

  NewMinImagePrototype(&src, width, height, channels, type);
  NewMinImagePrototype(&dst, width, height, channels, type);

  for (auto _ : state) {
    MergeImage(&dst, &src, &src, BIOP_ADD);
  }

  state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) * width * height * channels);
}

BENCHMARK_CAPTURE(Benchmark, Example1, TYP_UINT8, 3)
    ->Name("op:BinarySum/lib:MinImg/ch:3/typ:TYP_UINT8")
    ->Ranges({{2, 1000}, {2, 1000}})
    ->ArgNames({"img_w", "img_h"});

BENCHMARK_MAIN();
