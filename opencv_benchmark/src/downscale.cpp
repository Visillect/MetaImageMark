#include <grid_benchmark.h>

#include <config.h>
#include <description_generators.h>
#include <image_generators.h>

void ScalePixel() {
  auto operation = [](generators::ImagePair& pair) {
    cv::resize(pair.src, pair.dest, pair.dest.size(), 0, 0,
               cv::InterpolationFlags::INTER_AREA);
  };

  grid_benchmark::AddGridBenchmark(
      description::Scale("ScalePixel"), generators::ScalePair, operation,
      kImageTypes, kDownScale, kChannels, kImageSide, kImageSide);
}

void ScaleSubPixel() {
  auto operation = [](generators::ImagePair& pair) {
    cv::resize(pair.src, pair.dest, pair.dest.size(), 0, 0,
               cv::InterpolationFlags::INTER_LINEAR_EXACT);
  };

  grid_benchmark::AddGridBenchmark(
      description::Scale("ScaleSubPixel"), generators::ScalePair, operation,
      kImageTypes, kDownScale, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  ScalePixel();
  ScaleSubPixel();

  grid_benchmark::Run(argc, argv);
}
