#include <benchmark/benchmark.h>

#include <imgprcbench/benchmark.h>
#include <imgprcbench/custom_arguments.h>

using imgprcbench::BinaryRandomImageBenchmark;

static void CustomImageSize(benchmark::internal::Benchmark* bench) {
  imgprcbench::MakeImageGridLogSizes(bench, {1, 1000}, {1, 1000}, 15, 15);
}

#define IMG_BENCHMARK(library, library_ns, operation, type, channel_count)                  \
  BENCHMARK_CAPTURE(BinaryRandomImageBenchmark, BinaryRandomImageBenchmark,                 \
                    library_ns::LibrarySuite(), library_ns::operation, type, channel_count) \
      ->Name("lib:" #library "/typ:" #type "/ch:" #channel_count "/op:" #operation)         \
      ->Apply(CustomImageSize)                                                              \
      ->MinTime(0.025)                                                                      \
      ->Repetitions(3)

#define IMG_BENCHMARK_GROUP(library, library_ns, operation)     \
  IMG_BENCHMARK(library, library_ns, operation, TYP_UINT8, 1);  \
  IMG_BENCHMARK(library, library_ns, operation, TYP_UINT8, 3);  \
  IMG_BENCHMARK(library, library_ns, operation, TYP_INT32, 1);  \
  IMG_BENCHMARK(library, library_ns, operation, TYP_INT32, 3);  \
  IMG_BENCHMARK(library, library_ns, operation, TYP_REAL32, 1); \
  IMG_BENCHMARK(library, library_ns, operation, TYP_REAL32, 3)

#define IMG_BENCHMARK_OPERATIONS(library, library_ns)                 \
  IMG_BENCHMARK_GROUP(library, library_ns, BinarySum);                \
  IMG_BENCHMARK_GROUP(library, library_ns, BinaryDifference);         \
  IMG_BENCHMARK_GROUP(library, library_ns, BinaryAbsoluteDifference); \
  IMG_BENCHMARK_GROUP(library, library_ns, BinaryMultiplication)
