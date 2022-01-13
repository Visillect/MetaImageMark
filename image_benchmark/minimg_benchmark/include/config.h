#pragma once

#include <array>

#include <minbase/mintyp.h>

constexpr std::array<int, 15> kImageSide{1,  2,  3,   4,   7,   12,  19,  32,
                                         52, 85, 139, 228, 373, 611, 1000};
constexpr std::array<MinTyp, 10> kImageTypes{
    TYP_INT8,   TYP_UINT8, TYP_INT16,  TYP_UINT16, TYP_INT32,
    TYP_UINT32, TYP_INT64, TYP_UINT64, TYP_REAL32, TYP_REAL64};
constexpr std::array<int, 1> kChannels{1};
constexpr std::array<double, 6> kDownScale{0.67, 0.5, 0.34, 0.25, 0.2, 0.17};
constexpr std::array<int, 5> kBoxSize{2, 5, 10, 100, 300};
constexpr std::array<double, 10> kSigmas{0.0, 0.1, 0.5, 1.0,  1.5,
                                         2.0, 3.0, 5.0, 20.0, 50.0};
