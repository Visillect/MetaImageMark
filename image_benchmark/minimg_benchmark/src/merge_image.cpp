#include <grid_benchmark.h>

#include "common.h"

ImageTriplet GenerateTriplet(MinTyp type, int ch, int w, int h) {
  auto generate = [=]() {
    return GenerateRandomImage(type, ch, w, h);
  };
  return ImageTriplet{generate(), generate(), generate()};
}

auto MakeDescriptionGenerator(std::string operation) {
  return [operation = std::move(operation)](MinTyp type, int ch, int w, int h) {
    return KVContainer{{"op", operation},
                       {"MinType", GetMinTypeString(type)},
                       {"ch", std::to_string(ch)},
                       {"w", std::to_string(w)},
                       {"h", std::to_string(h)}};
  };
}

void BinarySum(ImageTriplet& triplet) {
  auto& [output, first, second] = triplet;
  THROW_ON_ERROR(MergeImage(output.get(), first.get(), second.get(), BIOP_ADD));
}

void BinaryDifference(ImageTriplet& triplet) {
  auto& [output, first, second] = triplet;
  THROW_ON_ERROR(MergeImage(output.get(), first.get(), second.get(), BIOP_DIF));
}

void BinaryAbsoluteDifference(ImageTriplet& triplet) {
  auto& [output, first, second] = triplet;
  THROW_ON_ERROR(MergeImage(output.get(), first.get(), second.get(), BIOP_ADF));
}

void BinaryMultiplication(ImageTriplet& triplet) {
  auto& [output, first, second] = triplet;
  THROW_ON_ERROR(MergeImage(output.get(), first.get(), second.get(), BIOP_MUL));
}

void BinaryDivision(ImageTriplet& triplet) {
  auto& [output, first, second] = triplet;
  THROW_ON_ERROR(MergeImage(output.get(), first.get(), second.get(), BIOP_DIV));
}

void BinaryPow(ImageTriplet& triplet) {
  auto& [output, first, second] = triplet;
  THROW_ON_ERROR(MergeImage(output.get(), first.get(), second.get(), BIOP_POW));
}

int main(int argc, char* argv[]) {
  //// BinarySum
  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinarySum"),
                                   GenerateTriplet, BinarySum, kImageTypes,
                                   kOneChannel, kImageSide, kImageSide);

  //// BinaryDiff
  grid_benchmark::AddGridBenchmark(
      MakeDescriptionGenerator("BinaryDiff"), GenerateTriplet, BinaryDifference,
      kImageTypes, kOneChannel, kImageSide, kImageSide);

  //// BinaryADF
  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinaryADF"),
                                   GenerateTriplet, BinaryAbsoluteDifference,
                                   kImageTypes, kOneChannel, kImageSide,
                                   kImageSide);

  //// BinaryMult
  grid_benchmark::AddGridBenchmark(
      MakeDescriptionGenerator("BinaryMult"), GenerateTriplet,
      BinaryMultiplication, kImageTypes, kOneChannel, kImageSide, kImageSide);

  //// BinaryDiv
  // Doesn't work. Does not work. Most likely division by zero.
  // grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinaryDiv"),
  //                                   GenerateTriplet, BinaryDivision,
  //                                   kImageTypes, kChannels, kImageSide,
  //                                   kImageSide);

  //// BinaryPow
  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinaryPow"),
                                   GenerateTriplet, BinaryPow, kImageTypes,
                                   kOneChannel, kImageSide, kImageSide);

  grid_benchmark::Run(argc, argv);
}
