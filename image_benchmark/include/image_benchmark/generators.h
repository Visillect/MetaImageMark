#pragma once

#include <algorithm>
#include <cmath>

#include <image_benchmark/macros.h>

namespace image_benchmark {

////////////////////////////////////////////////////////////////////////////////

struct ImagePair {
  Image src;
  Image dest;
};

BENCH_INLINE ImagePair DoubleTypePairGen(ScalarType from_typ, ScalarType to_typ,
                                         int ch, int w, int h) {
  return {RandomImage(from_typ, ch, w, h), RandomImage(to_typ, ch, w, h)};
}

BENCH_INLINE ImagePair TransposePairGen(ScalarType typ, int ch, int w, int h) {
  return {RandomImage(typ, ch, w, h), RandomImage(typ, ch, h, w)};
}

BENCH_INLINE ImagePair EqualPairGen(ScalarType typ, int ch, int w, int h) {
  auto generate = [=]() {
    return RandomImage(typ, ch, w, h);
  };
  return {generate(), generate()};
}

BENCH_INLINE ImagePair ScalePairGen(ScalarType typ, double scale, int ch, int w,
                                    int h) {
  int dest_w = std::max<int>(std::round(scale * w), 1);
  int dest_h = std::max<int>(std::round(scale * h), 1);

  return {RandomImage(typ, ch, w, h), RandomImage(typ, ch, dest_w, dest_h)};
}

template <class T>
struct ImagePairWithValue : ImagePair {
  T value;
};

template <class T>
BENCH_INLINE ImagePairWithValue<T> ImagePairWithValueGen(ScalarType typ,
                                                         T value, int ch, int w,
                                                         int h) {
  auto generate = [=]() {
    return RandomImage(typ, ch, w, h);
  };
  return {generate(), generate(), value};
}

////////////////////////////////////////////////////////////////////////////////

struct ImageTriplet {
  Image src1;
  Image src2;
  Image dest;
};

BENCH_INLINE ImageTriplet EqualTripletGen(ScalarType typ, int ch, int w,
                                          int h) {
  auto generate = [=]() {
    return RandomImage(typ, ch, w, h);
  };
  return {generate(), generate(), generate()};
}

////////////////////////////////////////////////////////////////////////////////

}  // namespace image_benchmark
