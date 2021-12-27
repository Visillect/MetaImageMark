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

  SaveOperationResult(paths, argv[1], "_aver_minimg", minimg_benchmark::LibrarySuite(),
                      minimg_benchmark::AverFilter, 20, 10);

  SaveOperationResult(paths, argv[1], "_aver_opencv", opencv_benchmark::LibrarySuite(),
                      opencv_benchmark::AverFilter, 20, 10);

  return 0;
};
