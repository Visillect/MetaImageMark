#include <grid_benchmark.h>

#include "common.h"

ImagePair GeneratePair(MinTyp from_type, MinTyp to_type, int ch, int w, int h) {
  return {GenerateRandomImage(from_type, ch, w, h),
          GenerateRandomImage(to_type, ch, w, h)};
}

auto MakeDescriptionGenerator(std::string operation) {
  return [operation = std::move(operation)](MinTyp from_type, MinTyp to_type,
                                            int ch, int w, int h) {
    return KVContainer{{"lib", "MinImg"},
                       {"op", operation},
                       {"from_typ", GetMinTypeString(from_type)},
                       {"to_typ", GetMinTypeString(to_type)},
                       {"ch", std::to_string(ch)},
                       {"img_w", std::to_string(w)},
                       {"img_h", std::to_string(h)}};
  };
}

void Convert() {
  auto operation = [](ImagePair& pair) {
    auto& [first, second] = pair;
    THROW_ON_ERROR(ConvertImage(second.get(), first.get()));
  };

  grid_benchmark::AddGridBenchmark(
      MakeDescriptionGenerator("Convert"), GeneratePair, operation, kImageTypes,
      kImageTypes, kOneChannel, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  Convert();

  grid_benchmark::Run(argc, argv);
}
