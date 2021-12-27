#include <benchmark/benchmark.h>

#include <imgprcbench/benchmark.h>
#include <imgprcbench/custom_arguments.h>

using imgprcbench::UnaryRandomImageBenchmark;

static void CustomImageSize(benchmark::internal::Benchmark* bench) {
  imgprcbench::MakeImageGridLogSizes(bench, {1, 1000}, {1, 1000}, 15, 15);
}

#define IMG_BENCHMARK_CONVERT(library, library_ns, operation, from_type, to_type, channel_count) \
  BENCHMARK_CAPTURE(UnaryRandomImageBenchmark, LinTransform, library_ns::LibrarySuite(),         \
                    library_ns::operation, from_type, to_type, channel_count)                    \
      ->Name("lib:" #library "/from_typ:" #from_type "/to_typ:" #to_type "/ch:" #channel_count   \
             "/op:" #operation)                                                                  \
      ->Apply(CustomImageSize)                                                                   \
      ->MinTime(0.02)                                                                            \
      ->Repetitions(2)

#define IMG_BENCHMARK_CONVERT_TO(library, library_ns, operation, to, channel_count)        \
  IMG_BENCHMARK_CONVERT(library, library_ns, operation, TYP_UINT8, to, channel_count);  \
  IMG_BENCHMARK_CONVERT(library, library_ns, operation, TYP_INT8, to, channel_count);  \
  IMG_BENCHMARK_CONVERT(library, library_ns, operation, TYP_UINT16, to, channel_count);  \
  IMG_BENCHMARK_CONVERT(library, library_ns, operation, TYP_INT16, to, channel_count);  \
  IMG_BENCHMARK_CONVERT(library, library_ns, operation, TYP_UINT32, to, channel_count);  \
  IMG_BENCHMARK_CONVERT(library, library_ns, operation, TYP_INT32, to, channel_count);  \
  IMG_BENCHMARK_CONVERT(library, library_ns, operation, TYP_UINT64, to, channel_count);  \
  IMG_BENCHMARK_CONVERT(library, library_ns, operation, TYP_INT64, to, channel_count);  \
  IMG_BENCHMARK_CONVERT(library, library_ns, operation, TYP_REAL32, to, channel_count);  \
  IMG_BENCHMARK_CONVERT(library, library_ns, operation, TYP_REAL64, to, channel_count);

#define IMG_BENCHMARK_CONVERT_GROUP(library, library_ns, operation)                 \
  IMG_BENCHMARK_CONVERT_TO(library, library_ns, operation, TYP_UINT8, 1);  \
  IMG_BENCHMARK_CONVERT_TO(library, library_ns, operation, TYP_INT8, 1);   \
  IMG_BENCHMARK_CONVERT_TO(library, library_ns, operation, TYP_UINT16, 1); \
  IMG_BENCHMARK_CONVERT_TO(library, library_ns, operation, TYP_INT16, 1);  \
  IMG_BENCHMARK_CONVERT_TO(library, library_ns, operation, TYP_UINT32, 1); \
  IMG_BENCHMARK_CONVERT_TO(library, library_ns, operation, TYP_INT32, 1);  \
  IMG_BENCHMARK_CONVERT_TO(library, library_ns, operation, TYP_UINT64, 1); \
  IMG_BENCHMARK_CONVERT_TO(library, library_ns, operation, TYP_INT64, 1);  \
  IMG_BENCHMARK_CONVERT_TO(library, library_ns, operation, TYP_REAL32, 1); \
  IMG_BENCHMARK_CONVERT_TO(library, library_ns, operation, TYP_REAL64, 1);
