#include <opencv_benchmark/common.h>

void GaussFilter() {
  auto operation = [](image_benchmark::ImagePairWithValue<double>& pair) {
    int half_height = std::max(1, static_cast<int>(pair.value * 3 + .5));
    int size = half_height * 2 + 1;

    cv::GaussianBlur(pair.src, pair.dest, cv::Size(size, size), pair.value, 0,
                     cv::BORDER_REPLICATE);
  };

  grid_benchmark::AddGridBenchmark(
      image_benchmark::GaussFilter("GaussFilter"),
      image_benchmark::ImagePairWithValueGen<double>, operation, kImageTypes,
      kSigmas, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  GaussFilter();

  grid_benchmark::Run(argc, argv);
}
