#pragma once

#include <memory>

#include <minbase/minimg.h>

#include <benchmark/benchmark.h>

#include <imgprcbench/generators.h>
#include <imgprcbench/utility.h>

namespace imgprcbench {

////////////////////////////////////////////////////////////////////////////////////////////////////

// Library image type support

////////////////////////////////////////////////////////////////////////////////////////////////////

class LibrarySuite {
 public:
  /**
   * Creates new library image header from MinImg image.
   * The image data must not be copied.
   *
   * @tparam Image - library image type
   * @param image - image to be converted
   * @return unique pointer to Image header
   */
  template <class Image>
  std::unique_ptr<Image> HeaderConvert(const MinImg& /*image*/) {
    return nullptr;
  }

  /**
   * Creates new MinImg header of image.
   * The image data must not be copied.
   *
   * @tparam Image - library image type
   * @param image - image to be converted
   * @return unique pointer to MinImage header
   */
  template <class Image>
  std::unique_ptr<MinImg> HeaderConvert(const Image& /*image*/) {
    return nullptr;
  }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

// Benchmark functions

////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Library, class Operation, class... Param>
void BinaryOperationBenchmark(benchmark::State& state, Library library, Operation operation,
                              MinImg& output, const MinImg& first, const MinImg& second,
                              const Param&... param) {
  try {
    auto first_converted = ConvertImage(library, first);
    auto second_converted = ConvertImage(library, second);
    auto output_converted = ConvertImage(library, output);

    for (auto _ : state) {
      operation(*output_converted, *first_converted, *second_converted, param...);
    }
  } catch (std::exception& exception) {
    state.SkipWithError(exception.what());
  }

  state.SetBytesProcessed((GetImageByteSize(first) + GetImageByteSize(second)) *
                          state.iterations());
}

template <class Library, class Operation, class... Param>
void UnaryOperationBenchmark(benchmark::State& state, Library library, Operation operation,
                             MinImg& output, const MinImg& input, const Param&... param) {
  try {
    auto input_converted = ConvertImage(library, input);
    auto output_converted = ConvertImage(library, output);

    for (auto _ : state) {
      operation(*output_converted, *input_converted, param...);
    }
  } catch (std::exception& exception) {
    state.SkipWithError(exception.what());
  }

  state.SetBytesProcessed(GetImageByteSize(input) * state.iterations());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// Benchmark functions with random images

////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Library, class Operation, class... Param>
void BinaryRandomImageBenchmark(benchmark::State& state, Library library, Operation operation,
                                MinTyp type, int channels, const Param&... param) {
  auto height = state.range(0);
  auto width = state.range(1);

  auto left = GenerateRandomImage(type, channels, width, height);
  auto right = GenerateRandomImage(type, channels, width, height);
  auto output = GenerateRandomImage(type, channels, width, height);

  BinaryOperationBenchmark(state, library, operation, *output, *left, *right, param...);
}

template <class Library, class Operation, class... Param>
void UnaryRandomImageBenchmark(benchmark::State& state, Library library, Operation operation,
                               MinTyp from, MinTyp to, int channels, const Param&... param) {
  auto height = state.range(0);
  auto width = state.range(1);

  auto input = GenerateRandomImage(from, channels, width, height);
  auto output = GenerateRandomImage(to, channels, width, height);

  UnaryOperationBenchmark(state, library, operation, *output, *input, param...);
}

template <class Library, class Operation, class... Param>
void UnaryRandomImageBenchmark(benchmark::State& state, Library library, Operation operation,
                               MinTyp type, int channels, const Param&... param) {
  UnaryRandomImageBenchmark(state, library, operation, type, type, channels, param...);
}

}  // namespace imgprcbench
