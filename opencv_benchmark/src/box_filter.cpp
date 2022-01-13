#include <grid_benchmark.h>

#include <config.h>
#include <description_generators.h>
#include <image_generators.h>

void BoxFilter() {
  auto operation = [](generators::ImagePairWithNumber& pair) {
    cv::boxFilter(pair.src, pair.dest, -1,
                  cv::Size(2 * pair.value + 1, 2 * pair.value + 1),
                  cv::Point(-1, -1), true, cv::BORDER_REPLICATE);
  };

  grid_benchmark::AddGridBenchmark(
      description::BoxFilter("BoxFilter"), generators::ImagePairNumber,
      operation, kImageTypes, kBoxSize, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  BoxFilter();

  grid_benchmark::Run(argc, argv);
}
