#include <initializer_list>
#include <utility>
#include <vector>

#include <gtest/gtest.h>
#include <meta_benchmark.h>

using meta_benchmark::internal::GenerateGrid;

TEST(OneParamGrid, INT) {
  std::vector<int> res;
  GenerateGrid(
      [&](int val) {
        res.push_back(val);
      },
      {1, 2, 3});

  std::vector<int> exp{1, 2, 3};
  ASSERT_EQ(res, exp);
}

TEST(TwoParamGrid, INT_STR) {
  std::vector<std::pair<int, std::string>> res;
  GenerateGrid(
      [&](int val, std::string str) {
        res.emplace_back(val, str);
      },
      {1, 2, 3}, {"ABC", "CBA"});

  std::vector<std::pair<int, std::string>> exp{
      {1, "ABC"}, {1, "CBA"}, {2, "ABC"}, {2, "CBA"}, {3, "ABC"}, {3, "CBA"}};
  ASSERT_EQ(res, exp);
}

TEST(ContainerType, Vectors) {
  std::vector<std::pair<int, int>> res;
  GenerateGrid(
      [&](int v1, int v2) {
        res.emplace_back(v1, v2);
      },
      std::vector<int>{1, 2, 3}, std::vector<int>{4, 5});

  std::vector<std::pair<int, int>> exp{{1, 4}, {1, 5}, {2, 4},
                                       {2, 5}, {3, 4}, {3, 5}};
  ASSERT_EQ(res, exp);
}
