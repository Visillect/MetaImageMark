#pragma once

#include <opencv2/core.hpp>

using Image = cv::Mat;

inline Image RandomImage(int scalar_type, int channel_count, int width,
                               int height) {
  cv::Mat image(height, width, CV_MAKE_TYPE(scalar_type, channel_count));
  std::vector<int> low(channel_count, 0);
  std::vector<int> high(channel_count, 255);

  cv::randu(image, low, high);

  return image;
}
