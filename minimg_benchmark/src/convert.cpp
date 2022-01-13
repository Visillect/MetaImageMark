#include <grid_benchmark.h>

#include <config.h>
#include <description_generators.h>
#include <image_generators.h>

void Convert() {
  auto operation = [](generators::ImagePair& pair) {
    THROW_ON_ERROR(ConvertImage(pair.dest.get(), pair.src.get()));
  };

  grid_benchmark::AddGridBenchmark(
      description::DoubleType("Convert"), generators::DoubleTypePair, operation,
      kImageTypes, kImageTypes, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  Convert();

  grid_benchmark::Run(argc, argv);
}
