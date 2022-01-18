#pragma once

#include <string>

#include <minbase/mintyp.h>

using ScalarType = MinTyp;

inline std::string GetTypeString(ScalarType type) {
  switch (type) {
    case TYP_UINT1:
      return "UINT1";
    case TYP_UINT8:
      return "UINT8";
    case TYP_UINT16:
      return "UINT16";
    case TYP_UINT32:
      return "UINT32";
    case TYP_UINT64:
      return "UINT64";
    case TYP_INT8:
      return "INT8";
    case TYP_INT16:
      return "INT16";
    case TYP_INT32:
      return "INT32";
    case TYP_INT64:
      return "INT64";
    case TYP_REAL16:
      return "REAL16";
    case TYP_REAL32:
      return "REAL32";
    case TYP_REAL64:
      return "REAL64";
    default:
      throw std::runtime_error("Invalid type");
  }
}
