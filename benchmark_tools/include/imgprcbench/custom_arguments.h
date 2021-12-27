#pragma once

#include <cmath>

#include <benchmark/benchmark.h>

namespace imgprcbench {

struct Range {
  Range(int begin, int end) : begin{begin}, end{end} {
  }
  int begin;
  int end;
};

void MakeImageLogSizes(benchmark::internal::Benchmark* bench, Range width_range, Range height_range,
                       int count) {
  double width_ratio =
      std::pow(width_range.end / static_cast<double>(width_range.begin), 1. / (count - 1));
  double height_ratio =
      std::pow(height_range.end / static_cast<double>(height_range.begin), 1. / (count - 1));

  for (int index = 0; index < count; ++index) {
    int width = std::round(width_range.begin * std::pow(width_ratio, index));
    int height = std::round(height_range.begin * std::pow(height_ratio, index));
    bench->Args({height, width});
  }
  bench->ArgNames({"h", "w"});
}

void MakeImageGridLogSizes(benchmark::internal::Benchmark* bench, Range width_range,
                           Range height_range, int width_count, int height_count) {
  double width_ratio =
      std::pow(width_range.end / static_cast<double>(width_range.begin), 1. / (width_count - 1));
  double height_ratio =
      std::pow(height_range.end / static_cast<double>(height_range.begin), 1. / (height_count - 1));

  for (int row = 0; row < height_count; ++row) {
    int height = std::round(height_range.begin * std::pow(height_ratio, row));
    for (int col = 0; col < width_count; ++col) {
      int width = std::round(width_range.begin * std::pow(width_ratio, col));

      bench->Args({height, width});
    }
  }

  bench->ArgNames({"img_h", "img_w"});
}

}  // namespace imgprcbench
