#include <grid_benchmark.h>

#include "common.h"

ImagePair GeneratePair(MinTyp type, int ch, int w, int h) {
  return {GenerateRandomImage(type, ch, w, h),
          GenerateRandomImage(type, ch, h, w)};
}

auto MakeDescriptionGenerator(std::string operation) {
  return [operation = std::move(operation)](MinTyp type, int ch, int w, int h) {
    return KVContainer{{"lib", "MinImg"},
                       {"op", operation},
                       {"typ", GetMinTypeString(type)},
                       {"ch", std::to_string(ch)},
                       {"img_w", std::to_string(w)},
                       {"img_h", std::to_string(h)}};
  };
}

void Transpose() {
  auto operation = [](ImagePair& pair) {
    auto& [first, second] = pair;
    THROW_ON_ERROR(TransposeMinImage(second.get(), first.get()));
  };

  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("Transpose"),
                                   GeneratePair, operation, kImageTypes,
                                   kOneChannel, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  Transpose();

  grid_benchmark::Run(argc, argv);
}
