#include <utility>
#include <vector>

#include <grid_benchmark.h>
#include <gtest/gtest.h>

using grid_benchmark::internal::GenerateGrid;

TEST(OneParamGrid, INT) {
  std::vector<int> res;
  GenerateGrid(
      [&](int val) {
        res.push_back(val);
      },
      std::array<int, 3>{1, 2, 3});

  std::vector<int> exp{1, 2, 3};
  ASSERT_EQ(res, exp);
}

TEST(TwoParamGrid, INT_STR) {
  std::vector<std::pair<int, std::string>> res;
  GenerateGrid(
      [&](int val, std::string str) {
        res.emplace_back(val, str);
      },
      std::vector{1, 2, 3}, std::vector{"ABC", "CBA"});

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
      std::array<int, 3>{1, 2, 3}, std::array<int, 2>{4, 5});

  std::vector<std::pair<int, int>> exp{{1, 4}, {1, 5}, {2, 4},
                                       {2, 5}, {3, 4}, {3, 5}};
  ASSERT_EQ(res, exp);
}
