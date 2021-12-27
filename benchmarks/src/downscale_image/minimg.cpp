#include "config.h"

#include <minimg.h>

IMG_BENCHMARK_SCALE(MinImg, minimg_benchmark, ScalePixel);
IMG_BENCHMARK_SCALE(MinImg, minimg_benchmark, ScaleSubPixel);

BENCHMARK_MAIN();
