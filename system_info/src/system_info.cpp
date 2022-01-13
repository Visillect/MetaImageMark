#include <fstream>
#include <set>

#include <system_info.h>
#include "string_proc.h"

const std::string kCpuInfoPath{"/proc/cpuinfo"};
const std::map<std::string, std::string> kKeysMap{{"model name", "CPU"}};

std::pair<std::string, std::string> ParseCpuInfoLine(const std::string& line) {
  auto [left, right] = Split(line, ':');

  return {Trim(std::move(left)), Trim(std::move(right))};
}

SystemInfo GetSystemInfo() {
  SystemInfo result;

  std::ifstream info_stream(kCpuInfoPath);

  std::string line;
  while (std::getline(info_stream, line)) {
    auto [key, value] = ParseCpuInfoLine(line);
    if (kKeysMap.count(key) > 0) {
      result[kKeysMap.at(key)] = value;
    }
  }

  return result;
}
