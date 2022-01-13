#include <grid_benchmark.h>

#include <config.h>
#include <description_generators.h>
#include <image_generators.h>

void ScalePixel() {
  auto operation = [](generators::ImagePair& pair) {
    THROW_ON_ERROR(
        ScaleImage(pair.dest.get(), pair.src.get(), QualityOption::QO_PIXEL));
  };

  grid_benchmark::AddGridBenchmark(
      description::Scale("ScalePixel"), generators::ScalePair, operation,
      kImageTypes, kDownScale, kChannels, kImageSide, kImageSide);
}

void ScaleSubPixel() {
  auto operation = [](generators::ImagePair& pair) {
    THROW_ON_ERROR(ScaleImage(pair.dest.get(), pair.src.get(),
                              QualityOption::QO_SUBPIXEL));
  };

  grid_benchmark::AddGridBenchmark(
      description::Scale("ScaleSubPixel"), generators::ScalePair, operation,
      kImageTypes, kDownScale, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  ScalePixel();
  ScaleSubPixel();

  grid_benchmark::Run(argc, argv);
}
