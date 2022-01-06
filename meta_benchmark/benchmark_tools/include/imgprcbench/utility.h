#pragma once

#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <minimgio/minimgio.h>
#include <minimgprc/minimgprc.h>

namespace imgprcbench {

////////////////////////////////////////////////////////////////////////////////////////////////////

// Image byte size

////////////////////////////////////////////////////////////////////////////////////////////////////

size_t GetTypeSize(MinTyp type) {
  switch (type) {
    case TYP_UINT8:
    case TYP_INT8:
      return 1;
    case TYP_UINT16:
    case TYP_INT16:
    case TYP_REAL16:
      return 2;
    case TYP_UINT32:
    case TYP_INT32:
    case TYP_REAL32:
      return 4;
    case TYP_UINT64:
    case TYP_INT64:
    case TYP_REAL64:
      return 8;
    default:
      throw std::runtime_error(__func__ + std::string(": invalid type"));
  }
}

size_t GetImageByteSize(const MinImg& image) {
  return image.channels * image.width * image.height * GetTypeSize(image.scalar_type);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// Error handling

////////////////////////////////////////////////////////////////////////////////////////////////////

std::string DescribeError(int error) {
  switch (error) {
    case NO_ERRORS:
      return "NO_ERRORS";
    case BAD_ARGS:
      return "BAD_ARGS (One or more arguments passed to the function are not correct)";
    case NO_MEMORY:
      return "NO_MEMORY (Not enough memory is available)";
    case NOT_IMPLEMENTED:
      return "NOT_IMPLEMENTED (The requested function is not implemented)";
    case INTERNAL_ERROR:
      return "INTERNAL_ERROR (An internal error has occurred)";
    case FILE_ERROR:
      return "FILE_ERROR (An error occurred while working with files. The most likely cause is a "
             "full disk or a corrupted file to be open)";
    case NOT_SUPPORTED:
      return "NOT_SUPPORTED";
    case BAD_STATE:
      return "BAD_STATE";
    case NO_SENSE:
      return "NO_SENSE";
    default:
      throw std::runtime_error(__func__ + std::string(": invalid error"));
  }
}

#define THROW_ON_ERROR(call)                                                           \
  do {                                                                                 \
    int error = (call);                                                                \
    if (error != NO_ERRORS) {                                                          \
      throw std::runtime_error(__func__ + (": " + imgprcbench::DescribeError(error))); \
    }                                                                                  \
  } while (false)

////////////////////////////////////////////////////////////////////////////////////////////////////

// A smart pointer for automatic memory management

////////////////////////////////////////////////////////////////////////////////////////////////////

struct MinImgDeleter {
  void operator()(MinImg* image) {
    if (image != nullptr) {
      THROW_ON_ERROR(FreeMinImage(image));
    }
    delete image;
  }
};

using MinImgUniquePtr = std::unique_ptr<MinImg, MinImgDeleter>;

////////////////////////////////////////////////////////////////////////////////////////////////////

// Image input/output

////////////////////////////////////////////////////////////////////////////////////////////////////

MinImgUniquePtr LoadImage(const std::string& filename, int alignment = 16) {
  MinImgUniquePtr image{new MinImg{}};

  THROW_ON_ERROR(GetMinImageFileProps(image.get(), filename.c_str(), 0));

  THROW_ON_ERROR(AllocMinImage(image.get(), alignment));

  THROW_ON_ERROR(LoadMinImage(image.get(), filename.c_str()));

  return image;
}

void SaveImage(const std::string& filename, const MinImg& image) {
  THROW_ON_ERROR(SaveMinImage(filename.c_str(), &image));
}

template <class Depth>
void ConsoleOutput(const MinImg& image, std::ostream& os = std::cout) {
  constexpr int kPrecision = 4;

  THROW_ON_ERROR(AssureMinImageIsValid(&image));

  os << std::fixed << std::setprecision(kPrecision);
  os << "[";
  auto row_end = image.height * image.stride;
  for (int row_begin = 0; row_begin < row_end; row_begin += image.stride) {
    const auto* line = reinterpret_cast<const Depth*>(image.p_zero_line + row_begin);
    for (int col = 0; col < image.width; ++col) {
      os << "(";
      for (int ch = 0; ch < image.channels; ++ch) {
        os << +line[col * image.channels + ch] << (ch == image.channels - 1 ? "" : ", ");
      }
      os << (col == image.width - 1 ? ")" : ") ");
    }
    os << (row_begin == row_end - image.stride ? "" : ";\n");
  }
  os << "]" << std::endl;
}

void ConsoleOutput(const MinImg& image, std::ostream& os = std::cout) {
  THROW_ON_ERROR(AssureMinImageIsValid(&image));

  switch (image.scalar_type) {
    case TYP_UINT8:
      ConsoleOutput<uint8_t>(image, os);
      break;
    case TYP_UINT16:
      ConsoleOutput<uint16_t>(image, os);
      break;
    case TYP_UINT32:
      ConsoleOutput<uint32_t>(image, os);
      break;
    case TYP_UINT64:
      ConsoleOutput<uint64_t>(image, os);
      break;
    case TYP_INT8:
      ConsoleOutput<int8_t>(image, os);
      break;
    case TYP_INT16:
      ConsoleOutput<int16_t>(image, os);
      break;
    case TYP_INT32:
      ConsoleOutput<int32_t>(image, os);
      break;
    case TYP_INT64:
      ConsoleOutput<int64_t>(image, os);
      break;
    case TYP_REAL32:
      ConsoleOutput<real32_t>(image, os);
      break;
    case TYP_REAL64:
      ConsoleOutput<real64_t>(image, os);
      break;
    default:
      throw std::runtime_error(__func__ + std::string(": not supported type"));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// Image common operations wrappers

////////////////////////////////////////////////////////////////////////////////////////////////////

imgprcbench::MinImgUniquePtr DeepCopy(const MinImg& image) {
  imgprcbench::MinImgUniquePtr copy{new MinImg{}};

  THROW_ON_ERROR(CloneMinImagePrototype(copy.get(), &image));

  THROW_ON_ERROR(CopyMinImage(copy.get(), &image));

  return copy;
}

imgprcbench::MinImgUniquePtr FlipImage(const MinImg& image) {
  imgprcbench::MinImgUniquePtr flip{new MinImg{}};

  THROW_ON_ERROR(CloneMinImagePrototype(flip.get(), &image));

  THROW_ON_ERROR(FlipMinImage(flip.get(), &image, DO_HORIZONTAL));

  return flip;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// Support functions

////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Library>
auto ConvertImage(Library library, const MinImg& image) {
  auto converted = library.HeaderConvert(image);
  if (!converted) {
    throw std::runtime_error(__func__ + std::string(": bad conversion"));
  }
  return converted;
}

}  // namespace imgprcbench
