#pragma once

#include <algorithm>
#include <string>

static inline std::string RTrim(std::string string) {
  string.erase(std::find_if(string.rbegin(), string.rend(),
                            [](auto ch) {
                              return !std::isspace(ch);
                            })
                   .base(),
               string.end());
  return string;
}

static inline std::string LTrim(std::string string) {
  string.erase(string.begin(),
               std::find_if(string.begin(), string.end(), [](auto ch) {
                 return !std::isspace(ch);
               }));
  return string;
}

static inline std::string Trim(std::string string) {
  return LTrim(RTrim(string));
}

static inline std::pair<std::string, std::string> Split(
    const std::string& string, char delim) {
  auto delim_iter = std::find(string.begin(), string.end(), delim);
  if (delim_iter == string.end()) {
    return {string, ""};
  };

  return {std::string(string.begin(), delim_iter),
          std::string(std::next(delim_iter), string.end())};
}
