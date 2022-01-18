#pragma once

#include <algorithm>
#include <cmath>

namespace image_benchmark {

////////////////////////////////////////////////////////////////////////////////

struct ImagePair {
  Image src;
  Image dest;
};

inline ImagePair DoubleTypePairGen(ScalarType from_typ, ScalarType to_typ,
                                   int ch, int w, int h) {
  return {RandomImage(from_typ, ch, w, h), RandomImage(to_typ, ch, w, h)};
}

inline ImagePair TransposePairGen(ScalarType typ, int ch, int w, int h) {
  return {RandomImage(typ, ch, w, h), RandomImage(typ, ch, h, w)};
}

inline ImagePair EqualPairGen(ScalarType typ, int ch, int w, int h) {
  auto generate = [=]() {
    return RandomImage(typ, ch, w, h);
  };
  return {generate(), generate()};
}

inline ImagePair ScalePairGen(ScalarType typ, double scale, int ch, int w,
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
inline ImagePairWithValue<T> ImagePairWithValueGen(ScalarType typ, T value,
                                                   int ch, int w, int h) {
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

inline ImageTriplet EqualTripletGen(ScalarType typ, int ch, int w, int h) {
  auto generate = [=]() {
    return RandomImage(typ, ch, w, h);
  };
  return {generate(), generate(), generate()};
}

////////////////////////////////////////////////////////////////////////////////

}  // namespace image_benchmark
