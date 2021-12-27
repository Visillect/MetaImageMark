#include <imgprcbench/verification.h>

#include <minimg.h>
#include <opencv.h>

using imgprcbench::SaveOperationResult;

int main(int argc, char** argv) {
  std::vector<std::string> paths;
  if (argc < 3) {
    throw std::runtime_error("Wrong number of arguments");
  }
  for (int index = 2; index < argc; ++index) {
    paths.emplace_back(argv[index]);
  }

  SaveOperationResult(paths, argv[1], "_gauss_minimg", minimg_benchmark::LibrarySuite(),
                      minimg_benchmark::GaussFilter, 5.);

  SaveOperationResult(paths, argv[1], "_gauss_opencv", opencv_benchmark::LibrarySuite(),
                      opencv_benchmark::GaussFilter, 5.);

  return 0;
};
