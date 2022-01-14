#include <minimg_benchmark/common.h>

void GaussFilter() {
  auto operation = [](image_benchmark::ImagePairWithValue<double>& pair) {
    THROW_ON_ERROR(GaussFilterImage(pair.dest.get(), pair.src.get(), pair.value,
                                    pair.value, BorderOption::BO_REPEAT));
  };

  grid_benchmark::AddGridBenchmark(
      image_benchmark::GaussFilter("GaussFilter"),
      image_benchmark::ImagePairWithValueGen<double>, operation, kImageTypes,
      kSigmas, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  GaussFilter();

  grid_benchmark::Run(argc, argv);
}
