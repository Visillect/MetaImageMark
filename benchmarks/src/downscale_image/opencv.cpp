#include "config.h"

#include <opencv.h>

IMG_BENCHMARK_SCALE(OpenCV, opencv_benchmark, ScalePixel);
IMG_BENCHMARK_SCALE(OpenCV, opencv_benchmark, ScaleSubPixel);

BENCHMARK_MAIN();
