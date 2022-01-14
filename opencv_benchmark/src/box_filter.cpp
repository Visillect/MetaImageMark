#include <opencv_benchmark/common.h>

void BoxFilter() {
  auto operation = [](image_benchmark::ImagePairWithValue<int>& pair) {
    cv::boxFilter(pair.src, pair.dest, -1,
                  cv::Size(2 * pair.value + 1, 2 * pair.value + 1),
                  cv::Point(-1, -1), true, cv::BORDER_REPLICATE);
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::BoxFilter("BoxFilter"),
                                   image_benchmark::ImagePairWithValueGen<int>,
                                   operation, kImageTypes, kBoxSize, kChannels,
                                   kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  BoxFilter();

  grid_benchmark::Run(argc, argv);
}
