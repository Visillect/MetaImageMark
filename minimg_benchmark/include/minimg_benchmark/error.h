#pragma once

#include <stdexcept>
#include <string>

#include <image_benchmark/macros.h>
#include <minbase/minresult.h>

#define THROW_ON_ERROR(call)                                              \
  do {                                                                    \
    int error = (call);                                                   \
    if (error != NO_ERRORS) {                                             \
      throw std::runtime_error(__func__ + (": " + DescribeError(error))); \
    }                                                                     \
  } while (false)

BENCH_INLINE std::string DescribeError(int error) {
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