#include <minimg.h>

#include <imgprcbench/benchmark.h>
#include <imgprcbench/custom_arguments.h>

using imgprcbench::BinaryRandomImageBenchmark;

static void CustomImageSize(benchmark::internal::Benchmark* bench) {
  imgprcbench::MakeImageGridLogSizes(bench, {1, 1000}, {1, 1000}, 15, 15);
}

BENCHMARK_CAPTURE(BinaryRandomImageBenchmark, Example3, minimg_benchmark::LibrarySuite(),
                  minimg_benchmark::BinarySum, TYP_UINT8, 3)
    ->Name("op:BinarySum/lib:MinImg/ch:3/typ:TYP_UINT8")
    ->Apply(CustomImageSize)
    ->MinTime(0.025);

BENCHMARK_MAIN();
