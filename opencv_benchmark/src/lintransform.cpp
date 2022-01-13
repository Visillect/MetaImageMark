#include <grid_benchmark.h>

#include <config.h>
#include <description_generators.h>
#include <image_generators.h>

void LinTransform() {
  constexpr double kAdd = 2.5;
  constexpr double kMultiply = 0.5;

  auto operation = [kAdd, kMultiply](generators::ImagePair& pair) {
    pair.src.convertTo(pair.dest, pair.dest.type(), kMultiply, kAdd);
  };

  grid_benchmark::AddGridBenchmark(
      description::DoubleType("LinTransform"), generators::DoubleTypePair,
      operation, kImageTypes, kImageTypes, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  LinTransform();

  grid_benchmark::Run(argc, argv);
}
