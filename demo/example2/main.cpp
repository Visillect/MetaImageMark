#include <imgprcbench/custom_arguments.h>
#include <imgprcbench/generators.h>

void Benchmark(benchmark::State& state, MinTyp type, int channels) {
  int height = static_cast<int>(state.range(0));
  int width = static_cast<int>(state.range(1));

  auto first = imgprcbench::GenerateRandomImage(type, channels, width, height);
  auto second = imgprcbench::GenerateRandomImage(type, channels, width, height);
  auto output = imgprcbench::GenerateRandomImage(type, channels, width, height);

  for (auto _ : state) {
    MergeImage(first.get(), second.get(), output.get(), BIOP_ADD);
  }

  state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) * width * height * channels);
}

void CustomImageSize(benchmark::internal::Benchmark* bench) {
  imgprcbench::MakeImageGridLogSizes(bench, {1, 1000}, {1, 1000}, 15, 15);
}

BENCHMARK_CAPTURE(Benchmark, Example2, TYP_UINT8, 3)
    ->Name("op:BinarySum/lib:MinImg/ch:3/typ:TYP_UINT8")
    ->Apply(CustomImageSize)
    ->MinTime(0.025);

BENCHMARK_MAIN();
