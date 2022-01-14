#include <opencv_benchmark/common.h>

void BinarySum() {
  auto operation = [](image_benchmark::ImageTriplet& triplet) {
    cv::add(triplet.src1, triplet.src2, triplet.dest);
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::SingleType("BinarySum"),
                                   image_benchmark::EqualTripletGen, operation,
                                   kImageTypes, kChannels, kImageSide,
                                   kImageSide);
}

void BinaryDifference() {
  auto operation = [](image_benchmark::ImageTriplet& triplet) {
    triplet.dest = triplet.src1 - triplet.src2;
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::SingleType("BinaryDiff"),
                                   image_benchmark::EqualTripletGen, operation,
                                   kImageTypes, kChannels, kImageSide,
                                   kImageSide);
}

void BinaryAbsoluteDifference() {
  auto operation = [](image_benchmark::ImageTriplet& triplet) {
    cv::absdiff(triplet.src1, triplet.src2, triplet.dest);
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::SingleType("BinaryADF"),
                                   image_benchmark::EqualTripletGen, operation,
                                   kImageTypes, kChannels, kImageSide,
                                   kImageSide);
}

void BinaryMultiplication() {
  auto operation = [](image_benchmark::ImageTriplet& triplet) {
    cv::multiply(triplet.src1, triplet.src2, triplet.dest);
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::SingleType("BinaryMult"),
                                   image_benchmark::EqualTripletGen, operation,
                                   kImageTypes, kChannels, kImageSide,
                                   kImageSide);
}

void BinaryDivision() {
  auto operation = [](image_benchmark::ImageTriplet& triplet) {
    cv::divide(triplet.src1, triplet.src2, triplet.dest);
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::SingleType("BinaryDiv"),
                                   image_benchmark::EqualTripletGen, operation,
                                   kImageTypes, kChannels, kImageSide,
                                   kImageSide);
}

int main(int argc, char* argv[]) {
  BinarySum();
  BinaryDifference();
  BinaryAbsoluteDifference();
  BinaryMultiplication();
  BinaryDivision();

  grid_benchmark::Run(argc, argv);
}
