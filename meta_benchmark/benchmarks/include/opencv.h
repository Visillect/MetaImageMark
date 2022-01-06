#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <minimgprc/minimgprc.h>

#include <imgprcbench/utility.h>

namespace opencv_benchmark {

////////////////////////////////////////////////////////////////////////////////////////////////////

int MinImgToOpenCvType(MinTyp type, int channels_count) {
  switch (type) {
    case TYP_UINT1:
      break;
    case TYP_UINT8:
      return CV_MAKETYPE(CV_8U, channels_count);
    case TYP_UINT16:
      return CV_MAKETYPE(CV_16U, channels_count);
    case TYP_UINT32:
      break;
    case TYP_UINT64:
      break;
    case TYP_INT8:
      return CV_MAKETYPE(CV_8S, channels_count);
    case TYP_INT16:
      return CV_MAKETYPE(CV_16S, channels_count);
    case TYP_INT32:
      return CV_MAKETYPE(CV_32S, channels_count);
    case TYP_INT64:
      break;
#if CV_MAJOR_VERSION >= 4
    case TYP_REAL16:
      return CV_MAKETYPE(CV_16F, channels_count);
#endif
    case TYP_REAL32:
      return CV_MAKETYPE(CV_32F, channels_count);
    case TYP_REAL64:
      return CV_MAKETYPE(CV_64F, channels_count);
    default:
      throw std::runtime_error(__func__ + std::string(": invalid type"));
  }
  throw std::runtime_error(__func__ + std::string(": not supported"));
}

MinTyp OpenCvToMinImgType(int opencv_type) {
  switch (opencv_type) {
    case CV_8U:
      return TYP_UINT8;
    case CV_16U:
      return TYP_UINT16;
    case CV_8S:
      return TYP_INT8;
    case CV_16S:
      return TYP_INT16;
    case CV_32S:
      return TYP_INT32;
#if CV_MAJOR_VERSION >= 4
    case CV_16F:
      return TYP_REAL16;
#endif
    case CV_32F:
      return TYP_REAL32;
    case CV_64F:
      return TYP_REAL64;
  }
  throw std::runtime_error(__func__ + std::string(": not supported"));
}

class LibrarySuite {
 public:
  std::unique_ptr<cv::Mat> HeaderConvert(const MinImg& image) {
    return std::make_unique<cv::Mat>(image.height, image.width,
                                     MinImgToOpenCvType(image.scalar_type, image.channels),
                                     image.p_zero_line, image.stride);
  }

  std::unique_ptr<MinImg> HeaderConvert(const cv::Mat& image) {
    auto min_image = std::make_unique<MinImg>();

    THROW_ON_ERROR(WrapAlignedBufferWithMinImage(min_image.get(), image.data, image.cols,
                                                 image.rows, image.channels(),
                                                 OpenCvToMinImgType(image.depth()), image.step));

    return min_image;
  }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

// OpenCv binary operations

////////////////////////////////////////////////////////////////////////////////////////////////////

void BinarySum(cv::Mat& output, const cv::Mat& first, const cv::Mat& second) {
  cv::add(first, second, output);
}

void BinaryDifference(cv::Mat& output, const cv::Mat& first, const cv::Mat& second) {
  output = first - second;
}

void BinaryAbsoluteDifference(cv::Mat& output, const cv::Mat& first, const cv::Mat& second) {
  cv::absdiff(first, second, output);
}

void BinaryMultiplication(cv::Mat& output, const cv::Mat& first, const cv::Mat& second) {
  cv::multiply(first, second, output);
}

void BinaryDivision(cv::Mat& output, const cv::Mat& first, const cv::Mat& second) {
  cv::divide(first, second, output);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// OpenCv unary operations

////////////////////////////////////////////////////////////////////////////////////////////////////

void UnaryAbs(cv::Mat& output, const cv::Mat& input) {
  output = cv::abs(input);
}

void UnarySqrt(cv::Mat& output, const cv::Mat& input) {
  cv::sqrt(input, output);
}

void LinTransform(cv::Mat& output, const cv::Mat& input, double mul, double add) {
  input.convertTo(output, output.type(), mul, add);
}

void ConvertImage(cv::Mat& output, const cv::Mat& input) {
  input.convertTo(output, output.type());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// OpenCv unary operations with a number

////////////////////////////////////////////////////////////////////////////////////////////////////

void UnaryAdd(cv::Mat& output, const cv::Mat& input, double value) {
  output = input + cv::Scalar(value);
}

void UnaryAbsoluteDifference(cv::Mat& output, const cv::Mat& input, double value) {
  cv::absdiff(input, cv::Scalar(value), output);
}

void UnaryMultiplication(cv::Mat& output, const cv::Mat& input, double value) {
  output = input * value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// OpenCv unary operations with channel

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////

// OpenCv linear filter

////////////////////////////////////////////////////////////////////////////////////////////////////

void AverFilter(cv::Mat& output, const cv::Mat& input, int hor_wing, int ver_wing) {
  cv::boxFilter(input, output, -1, cv::Size(2 * hor_wing + 1, 2 * ver_wing + 1), cv::Point(-1, -1),
                true, cv::BORDER_REPLICATE);
}

void GaussFilter(cv::Mat& output, const cv::Mat& input, double sigma) {
  int half_height = std::max(1, static_cast<int>(sigma * 3 + .5));
  int size = half_height * 2 + 1;

  cv::GaussianBlur(input, output, cv::Size(size, size), sigma, 0, cv::BORDER_REPLICATE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// OpenCv transpose

////////////////////////////////////////////////////////////////////////////////////////////////////

void Transpose(cv::Mat& output, const cv::Mat& input) {
  cv::transpose(input, output);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// OpenCv scale

////////////////////////////////////////////////////////////////////////////////////////////////////

void ScaleSubPixel(cv::Mat& output, const cv::Mat& input) {
  cv::resize(input, output, output.size(), 0, 0, cv::InterpolationFlags::INTER_LINEAR_EXACT);
}

void ScalePixel(cv::Mat& output, const cv::Mat& input) {
  cv::resize(input, output, output.size(), 0, 0, cv::InterpolationFlags::INTER_AREA);
}

}  // namespace opencv_benchmark
