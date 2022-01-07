#include <benchmark/benchmark.h>

#include <imgprcbench/benchmark.h>
#include <imgprcbench/custom_arguments.h>

using imgprcbench::GenerateRandomImage;
using imgprcbench::UnaryOperationBenchmark;

static void CustomImageSize(benchmark::internal::Benchmark* bench) {
  imgprcbench::MakeImageGridLogSizes(bench, {2, 1000}, {2, 1000}, 14, 14);
}

template <class Library, class Operation>
void ScaleRandomImageBenchmark(benchmark::State& state, Library library, Operation operation,
                               MinTyp type, int channels, double scale) {
  auto height = state.range(0);
  auto width = state.range(1);

  auto input = GenerateRandomImage(type, channels, width, height);
  auto output = GenerateRandomImage(type, channels, std::max<int>(1, width * scale),
                                    std::max<int>(1, height * scale));

  UnaryOperationBenchmark(state, library, operation, *output, *input);
}

#define IMG_BENCHMARK(library, library_ns, operation, type, channel_count, scale)                  \
  BENCHMARK_CAPTURE(ScaleRandomImageBenchmark, ScaleRandomImageBenchmark,                          \
                    library_ns::LibrarySuite(), library_ns::operation, type, channel_count, scale) \
      ->Name("lib:" #library "/typ:" #type "/ch:" #channel_count "/op:" #operation                 \
             "/scale:" #scale)                                                                     \
      ->Apply(CustomImageSize)                                                                     \
      ->MinTime(0.01)                                                                              \
      ->Repetitions(3)

#define IMG_BENCHMARK_GROUP(library, library_ns, operation, scale)     \
  IMG_BENCHMARK(library, library_ns, operation, TYP_UINT8, 1, scale);  \
  IMG_BENCHMARK(library, library_ns, operation, TYP_UINT8, 3, scale);  \
  IMG_BENCHMARK(library, library_ns, operation, TYP_INT32, 1, scale);  \
  IMG_BENCHMARK(library, library_ns, operation, TYP_INT32, 3, scale);  \
  IMG_BENCHMARK(library, library_ns, operation, TYP_REAL32, 1, scale); \
  IMG_BENCHMARK(library, library_ns, operation, TYP_REAL32, 3, scale)

#define IMG_BENCHMARK_SCALE(library, library_ns, operation)  \
  IMG_BENCHMARK_GROUP(library, library_ns, operation, 0.67); \
  IMG_BENCHMARK_GROUP(library, library_ns, operation, 0.5);  \
  IMG_BENCHMARK_GROUP(library, library_ns, operation, 0.34); \
  IMG_BENCHMARK_GROUP(library, library_ns, operation, 0.25); \
  IMG_BENCHMARK_GROUP(library, library_ns, operation, 0.2);  \
  IMG_BENCHMARK_GROUP(library, library_ns, operation, 0.17)
