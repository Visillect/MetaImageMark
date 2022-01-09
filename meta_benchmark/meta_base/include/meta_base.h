#pragma once

#include <exception>
#include <string>
#include <utility>

#include <benchmark/benchmark.h>

namespace std {

std::string to_string(std::string string) {  // NOLINT
  return string;
}

}  // namespace std

namespace meta_mark {

namespace internal {

template <class KVContainer>
std::string GenerateMarkName(const KVContainer& kv_description) {
  std::string result;

  for (const auto& [key, value] : kv_description) {
    result += std::to_string(key);
    result += ':';
    result += std::to_string(value);
    result += '/';
  }

  return result;
}

}  // namespace internal

template <class KVContainer, class Generator, class Operation,
          class ErrorDescription>
void AddMetaBenchmark(const KVContainer& kv_description, Generator&& generator,
                      Operation&& operation,
                      ErrorDescription&& error_to_string) {
  auto bm_function = [generator = std::forward<Generator>(generator),
                      operation = std::forward<Operation>(operation),
                      error_to_string = std::forward<ErrorDescription>(
                          error_to_string)](benchmark::State& state) mutable {
    auto meta_image = generator();
    try {
      for (auto _ : state) {
        operation(meta_image);
      }
    } catch (const std::exception& error) {
      state.SkipWithError(error_to_string(error).c_str());
    }
  };

  benchmark::RegisterBenchmark(
      internal::GenerateMarkName(kv_description).c_str(), bm_function);
}

template <class Callback, class Range>
void GenerateGrid(Callback callback, const Range& range) {
  for (const auto& value : range) {
    callback(value);
  }
}

template <class Callback, class T>
void GenerateGrid(Callback callback, const std::initializer_list<T>& range) {
  GenerateGrid<Callback, std::initializer_list<T>>(callback, range);
}

template <class Callback, class Range, class... Tail>
void GenerateGrid(Callback callback, const Range& range, const Tail&... tail) {
  for (const auto& value : range) {
    GenerateGrid(
        [&callback, &value](const auto&... values) {
          callback(value, values...);
        },
        tail...);
  }
}

template <class Callback, class T, class... Tail>
void GenerateGrid(Callback callback, const std::initializer_list<T>& range,
                  const std::initializer_list<Tail>&... tail) {
  GenerateGrid<Callback, std::initializer_list<T>,
               std::initializer_list<Tail...>>(callback, range, tail...);
}

}  // namespace meta_mark
