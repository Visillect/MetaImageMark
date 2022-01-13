#pragma once

#include <map>
#include <string>

using SystemInfo = std::map<std::string, std::string>;

SystemInfo GetSystemInfo();
