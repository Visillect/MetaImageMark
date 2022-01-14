#pragma once

#include <array>

#include <image_benchmark/types.h>
#include <minbase/mintyp.h>

const image_benchmark::Pair kLibrary{"lib", "MinImg"};

constexpr std::array<MinTyp, 10> kImageTypes{
    TYP_INT8,   TYP_UINT8, TYP_INT16,  TYP_UINT16, TYP_INT32,
    TYP_UINT32, TYP_INT64, TYP_UINT64, TYP_REAL32, TYP_REAL64};
