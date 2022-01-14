#include <minimg_benchmark/common.h>

void BoxFilter() {
  auto operation = [](image_benchmark::ImagePairWithValue<int>& pair) {
    THROW_ON_ERROR(AverFilterImage(pair.dest.get(), pair.src.get(), pair.value,
                                   pair.value, BorderOption::BO_REPEAT));
  };

  grid_benchmark::AddGridBenchmark(image_benchmark::BoxFilter("BoxFilter"),
                                   image_benchmark::ImagePairWithValueGen<int>,
                                   operation, kImageTypes, kBoxSize, kChannels,
                                   kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  BoxFilter();

  grid_benchmark::Run(argc, argv);
}
