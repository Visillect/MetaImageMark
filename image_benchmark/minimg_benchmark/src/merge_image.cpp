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

void BinarySum() {
  auto operation = [](ImageTriplet& triplet) {
    auto& [output, first, second] = triplet;
    THROW_ON_ERROR(
        MergeImage(output.get(), first.get(), second.get(), BIOP_ADD));
  };

  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinarySum"),
                                   GenerateTriplet, operation, kImageTypes,
                                   kOneChannel, kImageSide, kImageSide);
}

void BinaryDifference() {
  auto operation = [](ImageTriplet& triplet) {
    auto& [output, first, second] = triplet;
    THROW_ON_ERROR(
        MergeImage(output.get(), first.get(), second.get(), BIOP_DIF));
  };

  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinaryDiff"),
                                   GenerateTriplet, operation, kImageTypes,
                                   kOneChannel, kImageSide, kImageSide);
}

void BinaryAbsoluteDifference() {
  auto operation = [](ImageTriplet& triplet) {
    auto& [output, first, second] = triplet;
    THROW_ON_ERROR(
        MergeImage(output.get(), first.get(), second.get(), BIOP_ADF));
  };

  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinaryADF"),
                                   GenerateTriplet, operation, kImageTypes,
                                   kOneChannel, kImageSide, kImageSide);
}

void BinaryMultiplication() {
  auto operation = [](ImageTriplet& triplet) {
    auto& [output, first, second] = triplet;
    THROW_ON_ERROR(
        MergeImage(output.get(), first.get(), second.get(), BIOP_MUL));
  };

  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinaryMult"),
                                   GenerateTriplet, operation, kImageTypes,
                                   kOneChannel, kImageSide, kImageSide);
}

// Doesn't work. Does not work. Most likely division by zero.
void BinaryDivision() {
  auto operation = [](ImageTriplet& triplet) {
    auto& [output, first, second] = triplet;
    THROW_ON_ERROR(
        MergeImage(output.get(), first.get(), second.get(), BIOP_DIV));
  };

  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinaryDiv"),
                                   GenerateTriplet, operation, kImageTypes,
                                   kOneChannel, kImageSide, kImageSide);
}

void BinaryPow() {
  auto operation = [](ImageTriplet& triplet) {
    auto& [output, first, second] = triplet;
    THROW_ON_ERROR(
        MergeImage(output.get(), first.get(), second.get(), BIOP_POW));
  };

  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinaryPow"),
                                   GenerateTriplet, operation, kImageTypes,
                                   kOneChannel, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  BinarySum();
  BinaryDifference();
  BinaryAbsoluteDifference();
  BinaryMultiplication();
  BinaryPow();

  grid_benchmark::Run(argc, argv);
}
