#include <benchmark/benchmark.h>
#include <grid_benchmark/grid_benchmark.h>

namespace grid_benchmark {

void Run(int& argc, char* argv[]) {
  benchmark::Initialize(&argc, argv);

  for (const auto& [key, value] : GetSystemInfo()) {
    benchmark::AddCustomContext(key, value);
  }

  benchmark::RunSpecifiedBenchmarks();

  benchmark::Shutdown();
}
}  // namespace grid_benchmark
