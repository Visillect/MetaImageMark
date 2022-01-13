#include <grid_benchmark.h>

#include <config.h>
#include <description_generators.h>
#include <image_generators.h>

void Transpose() {
  auto operation = [](generators::ImagePair& pair) {
    cv::transpose(pair.src, pair.dest);
  };

  grid_benchmark::AddGridBenchmark(
      description::Image("Transpose"), generators::TransposePair, operation,
      kImageTypes, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  Transpose();

  grid_benchmark::Run(argc, argv);
}
