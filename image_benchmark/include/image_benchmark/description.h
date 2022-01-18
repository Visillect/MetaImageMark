#pragma once

#include <string>
#include <utility>
#include <vector>

#include <image_benchmark/types.h>

namespace image_benchmark {

namespace pairs {

inline Pair Operation(std::string operation) {
  return {"op", std::move(operation)};
}

inline Pair FromType(ScalarType typ) {
  return {"from_typ", GetTypeString(typ)};
}

inline Pair ToType(ScalarType typ) {
  return {"to_typ", GetTypeString(typ)};
}

inline Pair Type(ScalarType typ) {
  return {"typ", GetTypeString(typ)};
}

inline Pair Channels(int channels) {
  return {"ch", std::to_string(channels)};
}

inline Pair ImgWidth(int width) {
  return {"img_w", std::to_string(width)};
}

inline Pair ImgHeight(int height) {
  return {"img_h", std::to_string(height)};
}

inline Pair Scale(double scale) {
  return {"scale", std::to_string(scale)};
}

inline Pair BoxSize(int size) {
  return {"box_size", std::to_string(size)};
}

inline Pair Sigma(double sigma) {
  return {"sigma", std::to_string(sigma)};
}

}  // namespace pairs

inline auto SingleType(std::string operation) {
  return
      [operation = std::move(operation)](ScalarType typ, int ch, int w, int h) {
        return KVContainer{kLibrary,           pairs::Operation(operation),
                           pairs::Type(typ),   pairs::Channels(ch),
                           pairs::ImgWidth(w), pairs::ImgHeight(h)};
      };
}

inline auto DoubleType(std::string operation) {
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

inline auto Scale(std::string operation) {
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

inline auto BoxFilter(std::string operation) {
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

inline auto GaussFilter(std::string operation) {
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
