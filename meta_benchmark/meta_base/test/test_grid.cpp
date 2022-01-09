#include <gtest/gtest.h>
#include <meta_base.h>

using meta_mark::GenerateGrid;

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
