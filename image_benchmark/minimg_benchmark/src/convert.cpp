#include <grid_benchmark.h>

#include "common.h"
#include "config.h"

void Convert() {
  auto operation = [](ImagePair& pair) {
    auto& [first, second] = pair;
    THROW_ON_ERROR(ConvertImage(second.get(), first.get()));
  };

  grid_benchmark::AddGridBenchmark(
      MakeConvertDescriptionGenerator("Convert"), GenerateConvertPair,
      operation, kImageTypes, kImageTypes, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  Convert();

  grid_benchmark::Run(argc, argv);
}
