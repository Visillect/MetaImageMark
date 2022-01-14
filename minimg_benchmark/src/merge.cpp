#include <minimg_benchmark/common.h>

void BinarySum() {
  auto operation = [](image_benchmark::ImageTriplet& triplet) {
    THROW_ON_ERROR(MergeImage(triplet.dest.get(), triplet.src1.get(),
                              triplet.src2.get(), BIOP_ADD));
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::SingleType("BinarySum"),
                                   image_benchmark::EqualTripletGen, operation,
                                   kImageTypes, kChannels, kImageSide,
                                   kImageSide);
}

void BinaryDifference() {
  auto operation = [](image_benchmark::ImageTriplet& triplet) {
    THROW_ON_ERROR(MergeImage(triplet.dest.get(), triplet.src1.get(),
                              triplet.src2.get(), BIOP_DIF));
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::SingleType("BinaryDiff"),
                                   image_benchmark::EqualTripletGen, operation,
                                   kImageTypes, kChannels, kImageSide,
                                   kImageSide);
}

void BinaryAbsoluteDifference() {
  auto operation = [](image_benchmark::ImageTriplet& triplet) {
    THROW_ON_ERROR(MergeImage(triplet.dest.get(), triplet.src1.get(),
                              triplet.src2.get(), BIOP_ADF));
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::SingleType("BinaryADF"),
                                   image_benchmark::EqualTripletGen, operation,
                                   kImageTypes, kChannels, kImageSide,
                                   kImageSide);
}

void BinaryMultiplication() {
  auto operation = [](image_benchmark::ImageTriplet& triplet) {
    THROW_ON_ERROR(MergeImage(triplet.dest.get(), triplet.src1.get(),
                              triplet.src2.get(), BIOP_MUL));
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::SingleType("BinaryMult"),
                                   image_benchmark::EqualTripletGen, operation,
                                   kImageTypes, kChannels, kImageSide,
                                   kImageSide);
}

// Doesn't work. Most likely division by zero.
void BinaryDivision() {
  auto operation = [](image_benchmark::ImageTriplet& triplet) {
    THROW_ON_ERROR(MergeImage(triplet.dest.get(), triplet.src1.get(),
                              triplet.src2.get(), BIOP_DIV));
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::SingleType("BinaryDiv"),
                                   image_benchmark::EqualTripletGen, operation,
                                   kImageTypes, kChannels, kImageSide,
                                   kImageSide);
}

void BinaryPow() {
  auto operation = [](image_benchmark::ImageTriplet& triplet) {
    THROW_ON_ERROR(MergeImage(triplet.dest.get(), triplet.src1.get(),
                              triplet.src2.get(), BIOP_POW));
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::SingleType("BinaryPow"),
                                   image_benchmark::EqualTripletGen, operation,
                                   kImageTypes, kChannels, kImageSide,
                                   kImageSide);
}

int main(int argc, char* argv[]) {
  BinarySum();
  BinaryDifference();
  BinaryAbsoluteDifference();
  BinaryMultiplication();
  BinaryPow();

  grid_benchmark::Run(argc, argv);
}
