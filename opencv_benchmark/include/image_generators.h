#pragma once

#include <utility>

#include <common.h>

namespace generators {

////////////////////////////////////////////////////////////////////////////////

BENCH_INLINE cv::Mat RandomImage(int scalar_type, int channel_count, int width,
                                 int height) {
  cv::Mat image(height, width, CV_MAKE_TYPE(scalar_type, channel_count));
  std::vector<int> low(channel_count, 0);
  std::vector<int> high(channel_count, 255);

  cv::randu(image, low, high);

  return image;
}

////////////////////////////////////////////////////////////////////////////////

struct ImagePair {
  cv::Mat src;
  cv::Mat dest;
};

BENCH_INLINE ImagePair DoubleTypePair(int from_typ, int to_typ, int ch, int w,
                                      int h) {
  return {RandomImage(from_typ, ch, w, h), RandomImage(to_typ, ch, w, h)};
}

BENCH_INLINE ImagePair TransposePair(int typ, int ch, int w, int h) {
  return {RandomImage(typ, ch, w, h), RandomImage(typ, ch, h, w)};
}

BENCH_INLINE ImagePair EqualPair(int typ, int ch, int w, int h) {
  auto generate = [=]() {
    return RandomImage(typ, ch, w, h);
  };
  return {generate(), generate()};
}

BENCH_INLINE ImagePair ScalePair(int typ, double scale, int ch, int w, int h) {
  int dest_w = std::max<int>(std::round(scale * w), 1);
  int dest_h = std::max<int>(std::round(scale * h), 1);

  return {RandomImage(typ, ch, w, h), RandomImage(typ, ch, dest_w, dest_h)};
}

////////////////////////////////////////////////////////////////////////////////

struct ImageTriplet {
  cv::Mat src1;
  cv::Mat src2;
  cv::Mat dest;
};

BENCH_INLINE ImageTriplet EqualTriplet(int typ, int ch, int w, int h) {
  auto generate = [=]() {
    return RandomImage(typ, ch, w, h);
  };
  return {generate(), generate(), generate()};
}

////////////////////////////////////////////////////////////////////////////////

struct ImagePairWithNumber : ImagePair {
  int value;
};

BENCH_INLINE ImagePairWithNumber ImagePairNumber(int typ, int value, int ch,
                                                 int w, int h) {
  auto generate = [=]() {
    return RandomImage(typ, ch, w, h);
  };
  return {generate(), generate(), value};
}

////////////////////////////////////////////////////////////////////////////////

struct ImagePairWithFloat : ImagePair {
  double value;
};

BENCH_INLINE ImagePairWithFloat ImagePairFloat(int typ, double value, int ch,
                                               int w, int h) {
  auto generate = [=]() {
    return RandomImage(typ, ch, w, h);
  };
  return {generate(), generate(), value};
}

}  // namespace generators
