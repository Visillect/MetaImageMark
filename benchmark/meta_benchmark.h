#pragma once

#include <exception>
#include <string>
#include <utility>

#include <benchmark>

namespace std {

template <>
std::string to_string(std::string string) {
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

template <class KVContainer, class Generator, class Operation, class ErrorHandle>
void AddMetaBenchmark(const KVContainer& kv_description, Generator&& generator,
                      Operation&& operation, ErrorHandle&& error_to_string) {
  auto bm_function = [generator = std::forward<Generator>(generator),
                      operation = std::forward<Operation>(operation),
                      error_to_string = std::forward<ErrorString>(error_to_string)](
                         benchmark::State& state) mutable {
    auto meta_image = generator();
    try {
      for (auto _ : state) {
        operation(meta_image);
      }
    } catch (const std::exception& error) {
      state.SkipWithError(error_handle(error).c_str());
    }
  };

  benchmark::RegisterBenchmark(internal::GenerateMarkName(kv_description).c_str(), bm_function);
}

}  // namespace meta_mark
