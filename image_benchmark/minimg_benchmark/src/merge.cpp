#include <grid_benchmark.h>

#include "common.h"
#include "config.h"

void BinarySum() {
  auto operation = [](ImageTriplet& triplet) {
    auto& [output, first, second] = triplet;
    THROW_ON_ERROR(
        MergeImage(output.get(), first.get(), second.get(), BIOP_ADD));
  };

  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinarySum"),
                                   GenerateEqualTriplet, operation, kImageTypes,
                                   kChannels, kImageSide, kImageSide);
}

void BinaryDifference() {
  auto operation = [](ImageTriplet& triplet) {
    auto& [output, first, second] = triplet;
    THROW_ON_ERROR(
        MergeImage(output.get(), first.get(), second.get(), BIOP_DIF));
  };

  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinaryDiff"),
                                   GenerateEqualTriplet, operation, kImageTypes,
                                   kChannels, kImageSide, kImageSide);
}

void BinaryAbsoluteDifference() {
  auto operation = [](ImageTriplet& triplet) {
    auto& [output, first, second] = triplet;
    THROW_ON_ERROR(
        MergeImage(output.get(), first.get(), second.get(), BIOP_ADF));
  };

  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinaryADF"),
                                   GenerateEqualTriplet, operation, kImageTypes,
                                   kChannels, kImageSide, kImageSide);
}

void BinaryMultiplication() {
  auto operation = [](ImageTriplet& triplet) {
    auto& [output, first, second] = triplet;
    THROW_ON_ERROR(
        MergeImage(output.get(), first.get(), second.get(), BIOP_MUL));
  };

  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinaryMult"),
                                   GenerateEqualTriplet, operation, kImageTypes,
                                   kChannels, kImageSide, kImageSide);
}

// Doesn't work. Most likely division by zero.
void BinaryDivision() {
  auto operation = [](ImageTriplet& triplet) {
    auto& [output, first, second] = triplet;
    THROW_ON_ERROR(
        MergeImage(output.get(), first.get(), second.get(), BIOP_DIV));
  };

  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinaryDiv"),
                                   GenerateEqualTriplet, operation, kImageTypes,
                                   kChannels, kImageSide, kImageSide);
}

void BinaryPow() {
  auto operation = [](ImageTriplet& triplet) {
    auto& [output, first, second] = triplet;
    THROW_ON_ERROR(
        MergeImage(output.get(), first.get(), second.get(), BIOP_POW));
  };

  grid_benchmark::AddGridBenchmark(MakeDescriptionGenerator("BinaryPow"),
                                   GenerateEqualTriplet, operation, kImageTypes,
                                   kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  BinarySum();
  BinaryDifference();
  BinaryAbsoluteDifference();
  BinaryMultiplication();
  BinaryPow();

  grid_benchmark::Run(argc, argv);
}
