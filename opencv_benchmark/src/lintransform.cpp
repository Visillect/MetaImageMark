#include <opencv_benchmark/common.h>

void LinTransform() {
  constexpr double kAdd = 2.5;
  constexpr double kMultiply = 0.5;

  auto operation = [kAdd, kMultiply](image_benchmark::ImagePair& pair) {
    pair.src.convertTo(pair.dest, pair.dest.type(), kMultiply, kAdd);
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::DoubleType("LinTransform"),
                                   image_benchmark::DoubleTypePairGen,
                                   operation, kImageTypes, kImageTypes,
                                   kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  LinTransform();

  grid_benchmark::Run(argc, argv);
}
