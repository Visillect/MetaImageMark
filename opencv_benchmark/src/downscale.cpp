#include <opencv_benchmark/common.h>

void ScalePixel() {
  auto operation = [](image_benchmark::ImagePair& pair) {
    cv::resize(pair.src, pair.dest, pair.dest.size(), 0, 0,
               cv::InterpolationFlags::INTER_AREA);
  };

  grid_benchmark::AddGridBenchmark(
      image_benchmark::Scale("ScalePixel"), image_benchmark::ScalePairGen,
      operation, kImageTypes, kDownScale, kChannels, kImageSide, kImageSide);
}

void ScaleSubPixel() {
  auto operation = [](image_benchmark::ImagePair& pair) {
    cv::resize(pair.src, pair.dest, pair.dest.size(), 0, 0,
               cv::InterpolationFlags::INTER_LINEAR_EXACT);
  };

  grid_benchmark::AddGridBenchmark(
      image_benchmark::Scale("ScaleSubPixel"), image_benchmark::ScalePairGen,
      operation, kImageTypes, kDownScale, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  ScalePixel();
  ScaleSubPixel();

  grid_benchmark::Run(argc, argv);
}
