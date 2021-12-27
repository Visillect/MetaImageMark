#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <imgprcbench/utility.h>

namespace imgprcbench {

template <class Library, class Operation, class... Param>
void PerformBinaryOperation(Library library, Operation operation, MinImg& output,
                            const MinImg& first, const MinImg& second, const Param&... param) {
  auto first_converted = ConvertImage(library, first);
  auto second_converted = ConvertImage(library, second);
  auto output_converted = ConvertImage(library, output);

  operation(*output_converted, *first_converted, *second_converted, param...);
}

template <class Library, class Operation, class... Param>
void PerformUnaryOperation(Library library, Operation operation, MinImg& output,
                           const MinImg& input, const Param&... param) {
  auto input_converted = ConvertImage(library, input);
  auto output_converted = ConvertImage(library, output);

  operation(*output_converted, *input_converted, param...);
}

std::string GetFileName(const std::string& filepath) {
  size_t slash_index = filepath.size() - 1;
  while (filepath[slash_index] != '/' && slash_index > 0) {
    --slash_index;
  }

  return std::string{std::next(filepath.begin(), slash_index), filepath.end()};
}

std::string AddSuffix(const std::string& path, const std::string& suffix) {
  if (path.empty()) {
    throw std::runtime_error("invalid filepath");
  }

  size_t point_index = path.size() - 1;
  while (path[point_index] != '.' && point_index > 0) {
    --point_index;
  }

  if (path[point_index] != '.') {
    throw std::runtime_error("invalid filepath");
  }

  std::string result;
  std::copy(path.begin(), std::next(path.begin(), point_index), std::back_inserter(result));
  std::copy(suffix.begin(), suffix.end(), std::back_inserter(result));
  std::copy(std::next(path.begin(), point_index), path.end(), std::back_inserter(result));

  return result;
}

std::string GenerateOutputFilepath(const std::string& output_directory, const std::string& filepath,
                                   const std::string& suffix) {
  return output_directory + '/' + AddSuffix(GetFileName(filepath), suffix);
}

template <class Library, class Operation, class... Param>
void SaveOperationResult(const std::vector<std::string>& paths, const std::string& output_directory,
                         const std::string& output_suffix, Library library, Operation operation,
                         const Param&... param) {
  for (const auto& path : paths) {
    auto input = imgprcbench::LoadImage(path);
    auto output = imgprcbench::DeepCopy(*input);

    PerformUnaryOperation(library, operation, *output, *input, param...);

    imgprcbench::SaveImage(GenerateOutputFilepath(output_directory, path, output_suffix), *output);
  }
}

}  // namespace imgprcbench
