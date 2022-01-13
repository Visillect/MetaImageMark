#pragma once

#include <utility>

#include <common.h>
#include <minimgapi/test/minrandom.hpp>

namespace generators {

////////////////////////////////////////////////////////////////////////////////

BENCH_INLINE MinImgUniquePtr RandomImage(MinTyp scalar_type, int channel_count,
                                         int width, int height) {
  MinImgUniquePtr image{new MinImg{}};

  THROW_ON_ERROR(NewMinImagePrototype(image.get(), width, height, channel_count,
                                      scalar_type));

  THROW_ON_ERROR(ApplyLineFunctor(image.get(), Random255()));

  return image;
}

////////////////////////////////////////////////////////////////////////////////

struct ImagePair {
  MinImgUniquePtr src;
  MinImgUniquePtr dest;
};

BENCH_INLINE ImagePair DoubleTypePair(MinTyp from_typ, MinTyp to_typ, int ch,
                                      int w, int h) {
  return {RandomImage(from_typ, ch, w, h), RandomImage(to_typ, ch, w, h)};
}

BENCH_INLINE ImagePair TransposePair(MinTyp typ, int ch, int w, int h) {
  return {RandomImage(typ, ch, w, h), RandomImage(typ, ch, h, w)};
}

BENCH_INLINE ImagePair EqualPair(MinTyp typ, int ch, int w, int h) {
  auto generate = [=]() {
    return RandomImage(typ, ch, w, h);
  };
  return {generate(), generate()};
}

BENCH_INLINE ImagePair ScalePair(MinTyp typ, double scale, int ch, int w,
                                 int h) {
  int dest_w = std::max<int>(std::round(scale * w), 1);
  int dest_h = std::max<int>(std::round(scale * h), 1);

  return {RandomImage(typ, ch, w, h), RandomImage(typ, ch, dest_w, dest_h)};
}

////////////////////////////////////////////////////////////////////////////////

struct ImageTriplet {
  MinImgUniquePtr src1;
  MinImgUniquePtr src2;
  MinImgUniquePtr dest;
};

BENCH_INLINE ImageTriplet EqualTriplet(MinTyp typ, int ch, int w, int h) {
  auto generate = [=]() {
    return RandomImage(typ, ch, w, h);
  };
  return {generate(), generate(), generate()};
}

////////////////////////////////////////////////////////////////////////////////

struct ImagePairWithNumber : generators::ImagePair {
  int value;
};

ImagePairWithNumber ImagePairNumber(MinTyp typ, int value, int ch, int w,
                                    int h) {
  auto generate = [=]() {
    return RandomImage(typ, ch, w, h);
  };
  return {generate(), generate(), value};
};

}  // namespace generators
