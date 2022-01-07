#include <benchmark/benchmark.h>

#include <imgprcbench/benchmark.h>
#include <imgprcbench/custom_arguments.h>

using imgprcbench::UnaryRandomImageBenchmark;

static void CustomImageSize(benchmark::internal::Benchmark* bench) {
  imgprcbench::MakeImageGridLogSizes(bench, {1, 1000}, {1, 1000}, 10, 10);
}

#define IMG_BENCHMARK_GAUSS(library, library_ns, operation, type, channel_count, sigma_) \
  BENCHMARK_CAPTURE(UnaryRandomImageBenchmark, Gauss, library_ns::LibrarySuite(),        \
                    library_ns::operation, type, channel_count, sigma_)                  \
      ->Name("lib:" #library "/typ:" #type "/ch:" #channel_count "/op:" #operation       \
             "/sigma:" #sigma_)                                                          \
      ->Apply(CustomImageSize)                                                           \
      ->MinTime(0.025)                                                                   \
      ->Repetitions(2)

#define IMG_BENCHMARK_GAUSS_GROUP(library, library_ns, operation, sigma)    \
  IMG_BENCHMARK_GAUSS(library, library_ns, operation, TYP_UINT8, 1, sigma); \
  IMG_BENCHMARK_GAUSS(library, library_ns, operation, TYP_REAL32, 1, sigma);

#define IMG_BENCHMARK_GAUSS_GROUP_SIGMAS(library, library_ns, operation) \
  IMG_BENCHMARK_GAUSS_GROUP(library, library_ns, operation, 0.0);        \
  IMG_BENCHMARK_GAUSS_GROUP(library, library_ns, operation, 0.1);        \
  IMG_BENCHMARK_GAUSS_GROUP(library, library_ns, operation, 0.5);        \
  IMG_BENCHMARK_GAUSS_GROUP(library, library_ns, operation, 1.0);        \
  IMG_BENCHMARK_GAUSS_GROUP(library, library_ns, operation, 1.5);        \
  IMG_BENCHMARK_GAUSS_GROUP(library, library_ns, operation, 2.0);        \
  IMG_BENCHMARK_GAUSS_GROUP(library, library_ns, operation, 3.0);        \
  IMG_BENCHMARK_GAUSS_GROUP(library, library_ns, operation, 5.0);        \
  IMG_BENCHMARK_GAUSS_GROUP(library, library_ns, operation, 20.0);       \
  IMG_BENCHMARK_GAUSS_GROUP(library, library_ns, operation, 50.0);
