#include <grid_benchmark.h>

#include "common.h"
#include "config.h"

void Transpose() {
  auto operation = [](ImagePair& pair) {
    auto& [first, second] = pair;
    THROW_ON_ERROR(TransposeMinImage(second.get(), first.get()));
  };

  grid_benchmark::AddGridBenchmark(
      MakeDescriptionGenerator("Transpose"), GenerateTransposePair, operation,
      kImageTypes, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  Transpose();

  grid_benchmark::Run(argc, argv);
}
