#include <grid_benchmark.h>

#include <config.h>
#include <description_generators.h>
#include <image_generators.h>

void GaussFilter() {
  auto operation = [](generators::ImagePairWithFloat& pair) {
    int half_height = std::max(1, static_cast<int>(pair.value * 3 + .5));
    int size = half_height * 2 + 1;

    cv::GaussianBlur(pair.src, pair.dest, cv::Size(size, size), pair.value, 0,
                     cv::BORDER_REPLICATE);
  };

  grid_benchmark::AddGridBenchmark(
      description::GaussFilter("GaussFilter"), generators::ImagePairFloat,
      operation, kImageTypes, kSigmas, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  GaussFilter();

  grid_benchmark::Run(argc, argv);
}
