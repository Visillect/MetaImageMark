#include <grid_benchmark.h>

#include <config.h>
#include <description_generators.h>
#include <image_generators.h>

void BoxFilter() {
  auto operation = [](generators::ImagePairWithNumber& pair) {
    THROW_ON_ERROR(AverFilterImage(pair.dest.get(), pair.src.get(), pair.value,
                                   pair.value, BorderOption::BO_REPEAT));
  };

  grid_benchmark::AddGridBenchmark(
      description::BoxFilter("BoxFilter"), generators::ImagePairNumber,
      operation, kImageTypes, kBoxSize, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  BoxFilter();

  grid_benchmark::Run(argc, argv);
}
