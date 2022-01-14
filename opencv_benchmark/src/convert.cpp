#include <opencv_benchmark/common.h>

void Convert() {
  auto operation = [](image_benchmark::ImagePair& pair) {
    pair.src.convertTo(pair.dest, pair.dest.type());
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::DoubleType("Convert"),
                                   image_benchmark::DoubleTypePairGen,
                                   operation, kImageTypes, kImageTypes,
                                   kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  Convert();

  grid_benchmark::Run(argc, argv);
}
