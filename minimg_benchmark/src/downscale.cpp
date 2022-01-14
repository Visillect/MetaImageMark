#include <minimg_benchmark/common.h>

void ScalePixel() {
  auto operation = [](image_benchmark::ImagePair& pair) {
    THROW_ON_ERROR(
        ScaleImage(pair.dest.get(), pair.src.get(), QualityOption::QO_PIXEL));
  };

  grid_benchmark::AddGridBenchmark(
      image_benchmark::Scale("ScalePixel"), image_benchmark::ScalePairGen,
      operation, kImageTypes, kDownScale, kChannels, kImageSide, kImageSide);
}

void ScaleSubPixel() {
  auto operation = [](image_benchmark::ImagePair& pair) {
    THROW_ON_ERROR(ScaleImage(pair.dest.get(), pair.src.get(),
                              QualityOption::QO_SUBPIXEL));
  };

  grid_benchmark::AddGridBenchmark(
      image_benchmark::Scale("ScaleSubPixel"), image_benchmark::ScalePairGen,
      operation, kImageTypes, kDownScale, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  ScalePixel();
  ScaleSubPixel();

  grid_benchmark::Run(argc, argv);
}
