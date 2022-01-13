#include <grid_benchmark.h>

#include <config.h>
#include <description_generators.h>
#include <image_generators.h>

void BinarySum() {
  auto operation = [](generators::ImageTriplet& triplet) {
    cv::add(triplet.src1, triplet.src2, triplet.dest);
  };

  grid_benchmark::AddGridBenchmark(
      description::Image("BinarySum"), generators::EqualTriplet, operation,
      kImageTypes, kChannels, kImageSide, kImageSide);
}

void BinaryDifference() {
  auto operation = [](generators::ImageTriplet& triplet) {
    triplet.dest = triplet.src1 - triplet.src2;
  };

  grid_benchmark::AddGridBenchmark(
      description::Image("BinaryDiff"), generators::EqualTriplet, operation,
      kImageTypes, kChannels, kImageSide, kImageSide);
}

void BinaryAbsoluteDifference() {
  auto operation = [](generators::ImageTriplet& triplet) {
    cv::absdiff(triplet.src1, triplet.src2, triplet.dest);
  };

  grid_benchmark::AddGridBenchmark(
      description::Image("BinaryADF"), generators::EqualTriplet, operation,
      kImageTypes, kChannels, kImageSide, kImageSide);
}

void BinaryMultiplication() {
  auto operation = [](generators::ImageTriplet& triplet) {
    cv::multiply(triplet.src1, triplet.src2, triplet.dest);
  };

  grid_benchmark::AddGridBenchmark(
      description::Image("BinaryMult"), generators::EqualTriplet, operation,
      kImageTypes, kChannels, kImageSide, kImageSide);
}

void BinaryDivision() {
  auto operation = [](generators::ImageTriplet& triplet) {
    cv::divide(triplet.src1, triplet.src2, triplet.dest);
  };

  grid_benchmark::AddGridBenchmark(
      description::Image("BinaryDiv"), generators::EqualTriplet, operation,
      kImageTypes, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  BinarySum();
  BinaryDifference();
  BinaryAbsoluteDifference();
  BinaryMultiplication();
  BinaryDivision();

  grid_benchmark::Run(argc, argv);
}
