#include <benchmark/benchmark.h>

#include <imgprcbench/benchmark.h>
#include <imgprcbench/custom_arguments.h>

using imgprcbench::GenerateRandomImage;
using imgprcbench::UnaryOperationBenchmark;

static void CustomImageSize(benchmark::internal::Benchmark* bench) {
  imgprcbench::MakeImageGridLogSizes(bench, {1, 1000}, {1, 1000}, 15, 15);
}

template <class Library, class Operation>
void TransposeRandomImageBenchmark(benchmark::State& state, Library library, Operation operation,
                                   MinTyp type, int channels) {
  auto height = state.range(0);
  auto width = state.range(1);

  auto input = GenerateRandomImage(type, channels, width, height);
  auto output = GenerateRandomImage(type, channels, height, width);

  UnaryOperationBenchmark(state, library, operation, *output, *input);
}

#define IMG_BENCHMARK(library, library_ns, operation, type, channel_count)                  \
  BENCHMARK_CAPTURE(TransposeRandomImageBenchmark, TransposeRandomImageBenchmark,           \
                    library_ns::LibrarySuite(), library_ns::operation, type, channel_count) \
      ->Name("lib:" #library "/typ:" #type "/ch:" #channel_count "/op:" #operation)         \
      ->Apply(CustomImageSize)                                                              \
      ->MinTime(0.01)                                                                       \
      ->Repetitions(3)

#define IMG_BENCHMARK_GROUP(library, library_ns, operation)     \
  IMG_BENCHMARK(library, library_ns, operation, TYP_UINT8, 1);  \
  IMG_BENCHMARK(library, library_ns, operation, TYP_UINT8, 3);  \
  IMG_BENCHMARK(library, library_ns, operation, TYP_INT32, 1);  \
  IMG_BENCHMARK(library, library_ns, operation, TYP_INT32, 3);  \
  IMG_BENCHMARK(library, library_ns, operation, TYP_REAL32, 1); \
  IMG_BENCHMARK(library, library_ns, operation, TYP_REAL32, 3)
