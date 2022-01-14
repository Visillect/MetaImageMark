#pragma once

#include <string>
#include <utility>
#include <vector>

#include <image_benchmark/macros.h>
#include <image_benchmark/types.h>

namespace image_benchmark {

namespace pairs {

BENCH_INLINE Pair Operation(std::string operation) {
  return {"op", std::move(operation)};
}

BENCH_INLINE Pair FromType(ScalarType typ) {
  return {"from_typ", GetTypeString(typ)};
}

BENCH_INLINE Pair ToType(ScalarType typ) {
  return {"to_typ", GetTypeString(typ)};
}

BENCH_INLINE Pair Type(ScalarType typ) {
  return {"typ", GetTypeString(typ)};
}

BENCH_INLINE Pair Channels(int channels) {
  return {"ch", std::to_string(channels)};
}

BENCH_INLINE Pair ImgWidth(int width) {
  return {"img_w", std::to_string(width)};
}

BENCH_INLINE Pair ImgHeight(int height) {
  return {"img_h", std::to_string(height)};
}

BENCH_INLINE Pair Scale(double scale) {
  return {"scale", std::to_string(scale)};
}

BENCH_INLINE Pair BoxSize(int size) {
  return {"box_size", std::to_string(size)};
}

BENCH_INLINE Pair Sigma(double sigma) {
  return {"sigma", std::to_string(sigma)};
}

}  // namespace pairs

BENCH_INLINE auto SingleType(std::string operation) {
  return
      [operation = std::move(operation)](ScalarType typ, int ch, int w, int h) {
        return KVContainer{kLibrary,           pairs::Operation(operation),
                           pairs::Type(typ),   pairs::Channels(ch),
                           pairs::ImgWidth(w), pairs::ImgHeight(h)};
      };
}

BENCH_INLINE auto DoubleType(std::string operation) {
  return [operation = std::move(operation)](
             ScalarType from_typ, ScalarType to_typ, int ch, int w, int h) {
    return KVContainer{kLibrary,
                       pairs::Operation(operation),
                       pairs::FromType(from_typ),
                       pairs::ToType(to_typ),
                       pairs::Channels(ch),
                       pairs::ImgWidth(w),
                       pairs::ImgHeight(h)};
  };
}

BENCH_INLINE auto Scale(std::string operation) {
  return [operation = std::move(operation)](ScalarType typ, double scale,
                                            int ch, int w, int h) {
    return KVContainer{kLibrary,
                       pairs::Operation(operation),
                       pairs::Type(typ),
                       pairs::Scale(scale),
                       pairs::Channels(ch),
                       pairs::ImgWidth(w),
                       pairs::ImgHeight(h)};
  };
}

BENCH_INLINE auto BoxFilter(std::string operation) {
  return [operation = std::move(operation)](ScalarType typ, int box_size,
                                            int ch, int w, int h) {
    return KVContainer{kLibrary,
                       pairs::Operation(operation),
                       pairs::Type(typ),
                       pairs::BoxSize(box_size),
                       pairs::Channels(ch),
                       pairs::ImgWidth(w),
                       pairs::ImgHeight(h)};
  };
}

BENCH_INLINE auto GaussFilter(std::string operation) {
  return [operation = std::move(operation)](ScalarType typ, double sigma,
                                            int ch, int w, int h) {
    return KVContainer{kLibrary,
                       pairs::Operation(operation),
                       pairs::Type(typ),
                       pairs::Sigma(sigma),
                       pairs::Channels(ch),
                       pairs::ImgWidth(w),
                       pairs::ImgHeight(h)};
  };
}

}  // namespace image_benchmark
