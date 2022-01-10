#pragma once

#include <exception>
#include <string>
#include <utility>

#include <benchmark/benchmark.h>

namespace meta_mark {

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

}  // namespace internal

template <class KVContainer, class Generator, class Operation>
void AddMetaBenchmark(const KVContainer& kv_description, Generator&& generator,
                      Operation&& operation, double min_time = 0.02) {
  auto bm_function = [generator = std::forward<Generator>(generator),
                      operation = std::forward<Operation>(operation)](
                         benchmark::State& state) mutable {
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
      ->MinTime(min_time);
}

void Run(int& argc, char* argv[]) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();

  benchmark::Shutdown();
}

template <class Callback, class List>
void GenerateGrid(Callback callback, const List& list) {
  for (const auto& value : list) {
    callback(value);
  }
}

template <class Callback, class T>
void GenerateGrid(Callback callback, const std::initializer_list<T>& list) {
  GenerateGrid<Callback, std::initializer_list<T>>(callback, list);
}

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

template <class Callback, class T, class... Tail>
void GenerateGrid(Callback callback, const std::initializer_list<T>& list,
                  const std::initializer_list<Tail>&... tail) {
  GenerateGrid<Callback, std::initializer_list<T>,
               std::initializer_list<Tail...>>(callback, list, tail...);
}

}  // namespace meta_mark
