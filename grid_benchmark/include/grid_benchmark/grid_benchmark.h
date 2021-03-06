#pragma once

#include <exception>
#include <string>
#include <utility>

#include <benchmark/benchmark.h>
#include <system_info.h>

namespace grid_benchmark {

namespace internal {

template <class KVContainer>
std::string MakeBenchmarkName(const KVContainer& kv_description) {
  std::string result;
  for (const auto& [key, value] : kv_description) {
    result += key + ":" + value + "/";
  }
  result.pop_back();

  return result;
}

template <class Callback, class List>
void GenerateGrid(Callback callback, const List& list) {
  for (const auto& value : list) {
    callback(value);
  }
}

// TODO: add braced-init-list support
template <class Callback, class List, class... Tail>
void GenerateGrid(Callback callback, const List& list, const Tail&... tail) {
  for (const auto& value : list) {
    GenerateGrid(
        [&callback, &value](const auto&... values) {
          callback(value, values...);
        },
        tail...);
  }
}

}  // namespace internal

template <class KVContainer, class Generator, class Operation>
void AddBenchmark(const KVContainer& kv_description, Generator generator,
                  Operation operation) {
  constexpr size_t kRepetitionCount = 2;
  constexpr double kMinTime = 0.02;

  auto bm_function = [generator, operation](benchmark::State& state) mutable {
    auto meta_object = generator();
    try {
      for (auto _ : state) {
        operation(meta_object);
      }
    } catch (const std::exception& error) {
      state.SkipWithError(error.what());
    }
  };

  benchmark::RegisterBenchmark(
      internal::MakeBenchmarkName(kv_description).c_str(), bm_function)
      ->MinTime(kMinTime)
      ->Repetitions(kRepetitionCount);
}

template <class KVDescriptionGenerator, class Generator, class Operation,
          class... ParamList>
void AddGridBenchmark(KVDescriptionGenerator kv_description_generator,
                      Generator generator, Operation operation,
                      const ParamList&... param_list) {
  internal::GenerateGrid(
      [kv_description_generator, generator, operation](auto... params) mutable {
        auto current_generator = [generator, params...]() {
          return generator(params...);
        };
        AddBenchmark(kv_description_generator(params...), current_generator,
                     operation);
      },
      param_list...);
}

void Run(int& argc, char* argv[]);

}  // namespace grid_benchmark
