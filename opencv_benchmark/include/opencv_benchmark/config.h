#pragma once

#include <array>

#include <image_benchmark/types.h>
#include <opencv2/core.hpp>

const image_benchmark::Pair kLibrary{"lib", "OpenCV"};

constexpr std::array<int, 7> kImageTypes{CV_8U,  CV_8S,  CV_16U, CV_16S,
                                         CV_32S, CV_32F, CV_64F};
