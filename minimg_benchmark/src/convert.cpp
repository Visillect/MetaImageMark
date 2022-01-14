#include <minimg_benchmark/common.h>

void Convert() {
  auto operation = [](image_benchmark::ImagePair& pair) {
    THROW_ON_ERROR(ConvertImage(pair.dest.get(), pair.src.get()));
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
