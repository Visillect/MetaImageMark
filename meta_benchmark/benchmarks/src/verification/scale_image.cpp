#include <imgprcbench/generators.h>
#include <imgprcbench/verification.h>

#include <minimg.h>
#include <opencv.h>

using imgprcbench::GenerateOutputFilepath;
using imgprcbench::PerformUnaryOperation;

template <class Library, class Operation, class... Param>
void SaveScaleResult(const std::vector<std::string>& paths, const std::string& output_directory,
                     const std::string& output_suffix, Library library, Operation operation,
                     double width_scale, double height_scale) {
  for (const auto& path : paths) {
    auto input = imgprcbench::LoadImage(path);
    auto output = imgprcbench::GenerateRandomImage(input->scalar_type, input->channels,
                                                   std::max<int>(1, width_scale * input->width),
                                                   std::max<int>(1, height_scale * input->height));

    PerformUnaryOperation(library, operation, *output, *input);

    imgprcbench::SaveImage(GenerateOutputFilepath(output_directory, path, output_suffix), *output);
  }
}
int main(int argc, char** argv) {
  std::vector<std::string> paths;
  if (argc < 3) {
    throw std::runtime_error("Wrong number of arguments");
  }
  for (int index = 2; index < argc; ++index) {
    paths.emplace_back(argv[index]);
  }

  SaveScaleResult(paths, argv[1], "_pixel_scale_minimg", minimg_benchmark::LibrarySuite(),
                  minimg_benchmark::ScalePixel, 0.5, 2.0);

  SaveScaleResult(paths, argv[1], "_pixel_scale_opencv", opencv_benchmark::LibrarySuite(),
                  opencv_benchmark::ScalePixel, 0.5, 2.0);

  SaveScaleResult(paths, argv[1], "_subpixel_scale_minimg", minimg_benchmark::LibrarySuite(),
                  minimg_benchmark::ScaleSubPixel, 0.5, 2.0);

  SaveScaleResult(paths, argv[1], "_subpixel_scale_opencv", opencv_benchmark::LibrarySuite(),
                  opencv_benchmark::ScaleSubPixel, 0.5, 2.0);


  return 0;
};
