#pragma once

#include <initializer_list>

namespace meta_mark {

template <class Callback, class T>
void GenerateGrid(Callback callback, const std::initializer_list<T>& range) {
  for (const auto& value : range) {
    callback(value);
  }
}

template <class Callback, class Range>
void GenerateGrid(Callback callback, const Range& range) {
  for (const auto& value : range) {
    callback(value);
  }
}

template <class Callback, class T, class... Tail>
void GenerateGrid(Callback callback, const std::initializer_list<T>& range,
                  const std::initializer_list<Tail>&... tail) {
  for (const auto& value : range) {
    GenerateGrid(
        [&callback, &value](const auto&... values) {
          callback(value, values...);
        },
        tail...);
  }
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

}  // namespace meta_mark
