#include <benchmark/benchmark.h>

#include <imgprcbench/benchmark.h>
#include <imgprcbench/custom_arguments.h>

using imgprcbench::UnaryRandomImageBenchmark;

static void CustomImageSize(benchmark::internal::Benchmark* bench) {
  imgprcbench::MakeImageGridLogSizes(bench, {1, 1000}, {1, 1000}, 15, 15);
}

#define IMG_BENCHMARK_FILTER(library, library_ns, operation, type, channel_count, width, height) \
  BENCHMARK_CAPTURE(UnaryRandomImageBenchmark, Filter, library_ns::LibrarySuite(),               \
                    library_ns::operation, type, channel_count, width, height)                   \
      ->Name("lib:" #library "/typ:" #type "/ch:" #channel_count "/op:" #operation               \
             "/filt_w:" #width "/filt_h:" #height)                                               \
      ->Apply(CustomImageSize)                                                                   \
      ->MinTime(0.05)                                                                            \
      ->Repetitions(3)

#define IMG_BENCHMARK_FILTER_GROUP(library, library_ns, operation, width, height)    \
  IMG_BENCHMARK_FILTER(library, library_ns, operation, TYP_UINT8, 1, width, height); \
  IMG_BENCHMARK_FILTER(library, library_ns, operation, TYP_UINT8, 3, width, height); \
  IMG_BENCHMARK_FILTER(library, library_ns, operation, TYP_INT32, 1, width, height); \
  IMG_BENCHMARK_FILTER(library, library_ns, operation, TYP_INT32, 3, width, height)

#define IMG_BENCHMARK_FILTERS(library, library_ns, operation)           \
  IMG_BENCHMARK_FILTER_GROUP(library, library_ns, operation, 2, 2);     \
  IMG_BENCHMARK_FILTER_GROUP(library, library_ns, operation, 5, 5);     \
  IMG_BENCHMARK_FILTER_GROUP(library, library_ns, operation, 10, 10);   \
  IMG_BENCHMARK_FILTER_GROUP(library, library_ns, operation, 100, 100); \
  IMG_BENCHMARK_FILTER_GROUP(library, library_ns, operation, 300, 300)
