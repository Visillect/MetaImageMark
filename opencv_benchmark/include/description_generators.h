#pragma once

#include <string>
#include <vector>

#include <common.h>
#include <opencv2/opencv.hpp>

namespace description {

using Pair = std::pair<std::string, std::string>;
using KVContainer = std::vector<std::pair<std::string, std::string>>;

namespace pairs {

const Pair kLibrary{"lib", "OpenCV"};

BENCH_INLINE Pair Operation(std::string operation) {
  return {"op", std::move(operation)};
}

BENCH_INLINE Pair FromType(int typ) {
  return {"from_typ", GetTypeString(typ)};
}

BENCH_INLINE Pair ToType(int typ) {
  return {"to_typ", GetTypeString(typ)};
}

BENCH_INLINE Pair Type(int typ) {
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

BENCH_INLINE auto Image(std::string operation) {
  return [operation = std::move(operation)](int typ, int ch, int w, int h) {
    return KVContainer{pairs::kLibrary,    pairs::Operation(operation),
                       pairs::Type(typ),   pairs::Channels(ch),
                       pairs::ImgWidth(w), pairs::ImgHeight(h)};
  };
}

BENCH_INLINE auto DoubleType(std::string operation) {
  return [operation = std::move(operation)](int from_typ, int to_typ, int ch,
                                            int w, int h) {
    return KVContainer{pairs::kLibrary,           pairs::Operation(operation),
                       pairs::FromType(from_typ), pairs::ToType(to_typ),
                       pairs::Channels(ch),       pairs::ImgWidth(w),
                       pairs::ImgHeight(h)};
  };
}

BENCH_INLINE auto Scale(std::string operation) {
  return [operation = std::move(operation)](int typ, double scale, int ch,
                                            int w, int h) {
    return KVContainer{pairs::kLibrary,     pairs::Operation(operation),
                       pairs::Type(typ),    pairs::Scale(scale),
                       pairs::Channels(ch), pairs::ImgWidth(w),
                       pairs::ImgHeight(h)};
  };
}

BENCH_INLINE auto BoxFilter(std::string operation) {
  return [operation = std::move(operation)](int typ, int box_size, int ch,
                                            int w, int h) {
    return KVContainer{pairs::kLibrary,     pairs::Operation(operation),
                       pairs::Type(typ),    pairs::BoxSize(box_size),
                       pairs::Channels(ch), pairs::ImgWidth(w),
                       pairs::ImgHeight(h)};
  };
}

BENCH_INLINE auto GaussFilter(std::string operation) {
  return [operation = std::move(operation)](int typ, double sigma, int ch,
                                            int w, int h) {
    return KVContainer{pairs::kLibrary,     pairs::Operation(operation),
                       pairs::Type(typ),    pairs::Sigma(sigma),
                       pairs::Channels(ch), pairs::ImgWidth(w),
                       pairs::ImgHeight(h)};
  };
}

}  // namespace description
