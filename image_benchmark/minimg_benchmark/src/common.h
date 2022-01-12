#include <array>
#include <memory>
#include <utility>

#include <minbase/minimg.h>
#include <minbase/minresult.h>
#include <minimgapi/minimgapi.h>
#include <minimgprc/minimgprc.h>
#include <minimgapi/test/minrandom.hpp>

std::string DescribeError(int error) {
  switch (error) {
    case NO_ERRORS:
      return "NO_ERRORS";
    case BAD_ARGS:
      return "BAD_ARGS (One or more arguments passed to the function are not "
             "correct)";
    case NO_MEMORY:
      return "NO_MEMORY (Not enough memory is available)";
    case NOT_IMPLEMENTED:
      return "NOT_IMPLEMENTED (The requested function is not implemented)";
    case INTERNAL_ERROR:
      return "INTERNAL_ERROR (An internal error has occurred)";
    case FILE_ERROR:
      return "FILE_ERROR (An error occurred while working with files. The most "
             "likely cause is a "
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

#define THROW_ON_ERROR(call)                                              \
  do {                                                                    \
    int error = (call);                                                   \
    if (error != NO_ERRORS) {                                             \
      throw std::runtime_error(__func__ + (": " + DescribeError(error))); \
    }                                                                     \
  } while (false)

struct MinImgDeleter {
  void operator()(MinImg* image) {
    if (image != nullptr) {
      THROW_ON_ERROR(FreeMinImage(image));
    }
    delete image;
  }
};

using MinImgUniquePtr = std::unique_ptr<MinImg, MinImgDeleter>;

MinImgUniquePtr GenerateRandomImage(MinTyp scalar_type, int channel_count,
                                    int width, int height) {
  MinImgUniquePtr image{new MinImg{}};

  THROW_ON_ERROR(NewMinImagePrototype(image.get(), width, height, channel_count,
                                      scalar_type));

  THROW_ON_ERROR(ApplyLineFunctor(image.get(), Random255()));

  return image;
}

std::string GetMinTypeString(MinTyp type) {
  switch (type) {
    case TYP_UINT1:
      return "TYP_UINT1";
    case TYP_UINT8:
      return "TYP_UINT8";
    case TYP_UINT16:
      return "TYP_UINT16";
    case TYP_UINT32:
      return "TYP_UINT32";
    case TYP_UINT64:
      return "TYP_UINT64";
    case TYP_INT8:
      return "TYP_INT8";
    case TYP_INT16:
      return "TYP_INT16";
    case TYP_INT32:
      return "TYP_INT32";
    case TYP_INT64:
      return "TYP_INT64";
    case TYP_REAL16:
      return "TYP_REAL16";
    case TYP_REAL32:
      return "TYP_REAL32";
    case TYP_REAL64:
      return "TYP_REAL64";
    default:
      throw std::runtime_error("Invalid type");
  }
}

using KVContainer = std::vector<std::pair<std::string, std::string>>;
using ImagePair = std::pair<MinImgUniquePtr, MinImgUniquePtr>;
using ImageTriplet =
    std::tuple<MinImgUniquePtr, MinImgUniquePtr, MinImgUniquePtr>;

constexpr std::array<int, 15> kImageSide{1,  2,  3,   4,   7,   12,  19,  32,
                                         52, 85, 139, 228, 373, 611, 1000};
constexpr std::array<MinTyp, 10> kImageTypes{
    TYP_INT8,   TYP_UINT8, TYP_INT16,  TYP_UINT16, TYP_INT32,
    TYP_UINT32, TYP_INT64, TYP_UINT64, TYP_REAL32, TYP_REAL64};
constexpr std::array<int, 1> kOneChannel{1};
constexpr std::array<int, 2> kTwoChannels{1};
