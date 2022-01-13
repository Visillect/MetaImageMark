#include <grid_benchmark.h>

#include <config.h>
#include <description_generators.h>
#include <image_generators.h>

void GaussFilter() {
  auto operation = [](generators::ImagePairWithFloat& pair) {
    THROW_ON_ERROR(GaussFilterImage(pair.dest.get(), pair.src.get(), pair.value,
                                    pair.value, BorderOption::BO_REPEAT));
  };

  grid_benchmark::AddGridBenchmark(
      description::GaussFilter("GaussFilter"), generators::ImagePairFloat,
      operation, kImageTypes, kSigmas, kChannels, kImageSide, kImageSide);
}

int main(int argc, char* argv[]) {
  GaussFilter();

  grid_benchmark::Run(argc, argv);
}
