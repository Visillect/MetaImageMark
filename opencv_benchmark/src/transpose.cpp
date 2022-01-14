#include <opencv_benchmark/common.h>

void Transpose() {
  auto operation = [](image_benchmark::ImagePair& pair) {
    cv::transpose(pair.src, pair.dest);
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::SingleType("Transpose"),
                                   image_benchmark::TransposePairGen, operation,
                                   kImageTypes, kChannels, kImageSide,
                                   kImageSide);
}

int main(int argc, char* argv[]) {
  Transpose();

  grid_benchmark::Run(argc, argv);
}
