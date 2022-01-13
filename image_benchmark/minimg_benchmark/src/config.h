#pragma once

#include <minbase/mintyp.h>
#include <array>

constexpr std::array<int, 15> kImageSide{1,  2,  3,   4,   7,   12,  19,  32,
                                         52, 85, 139, 228, 373, 611, 1000};
constexpr std::array<MinTyp, 10> kImageTypes{
    TYP_INT8,   TYP_UINT8, TYP_INT16,  TYP_UINT16, TYP_INT32,
    TYP_UINT32, TYP_INT64, TYP_UINT64, TYP_REAL32, TYP_REAL64};
constexpr std::array<int, 1> kChannels{1};
