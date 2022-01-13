#include <grid_benchmark.h>

#include <config.h>
#include <description_generators.h>
#include <image_generators.h>

void LinTransform() {
  constexpr double kAdd = 2.5;
  constexpr double kMultiply = 0.5;

  auto operation = [kAdd, kMultiply](generators::ImagePair& pair) {
    THROW_ON_ERROR(LinTransformImage(pair.dest.get(), pair.src.get(), kMultiply,
                                     kAdd, PC_MEDIUM));
  };

  grid_benchmark::AddGridBenchmark(
      description::DoubleType("LinTransform"), generators::DoubleTypePair,
      operation, kImageTypes, kImageTypes, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  LinTransform();

  grid_benchmark::Run(argc, argv);
}
