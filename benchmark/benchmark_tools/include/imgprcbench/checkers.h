#pragma once

#include <cmath>
#include <stdexcept>

#include <minbase/minimg.h>
#include <minimgapi/test/mincompare.hpp>

namespace imgprcbench {

class ElementWiseChecker {
 public:
  explicit ElementWiseChecker(double eps) : eps_{eps} {
  }

  bool operator()(const MinImg& first, const MinImg& second) const {
    switch (first.scalar_type) {
      case TYP_UINT1:
        return CompareEps(first, second, false);
      case TYP_UINT8:
        return CompareEps(first, second, static_cast<uint8_t>(eps_));
      case TYP_UINT16:
        return CompareEps(first, second, static_cast<uint16_t>(eps_));
      case TYP_UINT32:
        return CompareEps(first, second, static_cast<uint32_t>(eps_));
      case TYP_UINT64:
        return CompareEps(first, second, static_cast<uint64_t>(eps_));
      case TYP_INT8:
        return CompareEps(first, second, static_cast<int8_t>(eps_));
      case TYP_INT16:
        return CompareEps(first, second, static_cast<int16_t>(eps_));
      case TYP_INT32:
        return CompareEps(first, second, static_cast<int32_t>(eps_));
      case TYP_INT64:
        return CompareEps(first, second, static_cast<int64_t>(eps_));
      case TYP_REAL16:
        throw std::runtime_error(__func__ + std::string(": not supported"));
      case TYP_REAL32:
        return CompareEps(first, second, static_cast<real32_t>(eps_));
      case TYP_REAL64:
        return CompareEps(first, second, static_cast<real64_t>(eps_));
      default:
        throw std::runtime_error(__func__ + std::string(": invalid MinTyp"));
    }
  }

 private:
  const double eps_{};
};

}  // namespace imgprcbench
