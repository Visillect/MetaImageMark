#include <grid_benchmark.h>

#include <config.h>
#include <description_generators.h>
#include <image_generators.h>

void BinarySum() {
  auto operation = [](generators::ImageTriplet& triplet) {
    THROW_ON_ERROR(MergeImage(triplet.dest.get(), triplet.src1.get(),
                              triplet.src2.get(), BIOP_ADD));
  };

  grid_benchmark::AddGridBenchmark(
      description::Image("BinarySum"), generators::EqualTriplet, operation,
      kImageTypes, kChannels, kImageSide, kImageSide);
}

void BinaryDifference() {
  auto operation = [](generators::ImageTriplet& triplet) {
    THROW_ON_ERROR(MergeImage(triplet.dest.get(), triplet.src1.get(),
                              triplet.src2.get(), BIOP_DIF));
  };

  grid_benchmark::AddGridBenchmark(
      description::Image("BinaryDiff"), generators::EqualTriplet, operation,
      kImageTypes, kChannels, kImageSide, kImageSide);
}

void BinaryAbsoluteDifference() {
  auto operation = [](generators::ImageTriplet& triplet) {
    THROW_ON_ERROR(MergeImage(triplet.dest.get(), triplet.src1.get(),
                              triplet.src2.get(), BIOP_ADF));
  };

  grid_benchmark::AddGridBenchmark(
      description::Image("BinaryADF"), generators::EqualTriplet, operation,
      kImageTypes, kChannels, kImageSide, kImageSide);
}

void BinaryMultiplication() {
  auto operation = [](generators::ImageTriplet& triplet) {
    THROW_ON_ERROR(MergeImage(triplet.dest.get(), triplet.src1.get(),
                              triplet.src2.get(), BIOP_MUL));
  };

  grid_benchmark::AddGridBenchmark(
      description::Image("BinaryMult"), generators::EqualTriplet, operation,
      kImageTypes, kChannels, kImageSide, kImageSide);
}

// Doesn't work. Most likely division by zero.
void BinaryDivision() {
  auto operation = [](generators::ImageTriplet& triplet) {
    THROW_ON_ERROR(MergeImage(triplet.dest.get(), triplet.src1.get(),
                              triplet.src2.get(), BIOP_DIV));
  };

  grid_benchmark::AddGridBenchmark(
      description::Image("BinaryDiv"), generators::EqualTriplet, operation,
      kImageTypes, kChannels, kImageSide, kImageSide);
}

void BinaryPow() {
  auto operation = [](generators::ImageTriplet& triplet) {
    THROW_ON_ERROR(MergeImage(triplet.dest.get(), triplet.src1.get(),
                              triplet.src2.get(), BIOP_POW));
  };

  grid_benchmark::AddGridBenchmark(
      description::Image("BinaryPow"), generators::EqualTriplet, operation,
      kImageTypes, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  BinarySum();
  BinaryDifference();
  BinaryAbsoluteDifference();
  BinaryMultiplication();
  BinaryPow();

  grid_benchmark::Run(argc, argv);
}
