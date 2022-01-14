#include <minimg_benchmark/common.h>

void Transpose() {
  auto operation = [](image_benchmark::ImagePair& pair) {
    THROW_ON_ERROR(TransposeMinImage(pair.dest.get(), pair.src.get()));
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
