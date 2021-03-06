#pragma once

#include <string>

#include <opencv_benchmark/image.h>

using ScalarType = int;

inline std::string GetTypeString(ScalarType type) {
  switch (type) {
    case CV_8U:
      return "UINT8";
    case CV_8S:
      return "INT8";
    case CV_16U:
      return "UINT16";
    case CV_16S:
      return "INT16";
    case CV_32S:
      return "INT32";
#if CV_MAJOR_VERSION >= 4
    case CV_16F:
      return "REAL16";
#endif
    case CV_32F:
      return "REAL32";
    case CV_64F:
      return "REAL64";
    default:
      throw std::runtime_error("Invalid type");
  }
}
