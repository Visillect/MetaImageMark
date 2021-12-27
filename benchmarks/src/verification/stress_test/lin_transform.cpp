#include <random>

#include <gtest/gtest.h>

#include <imgprcbench/checkers.h>
#include <imgprcbench/generators.h>
#include <imgprcbench/utility.h>
#include <imgprcbench/verification.h>

#include <minimg.h>
#include <opencv.h>

using imgprcbench::PerformUnaryOperation;

template <class FirstLibrary, class FirstOperation, class SecondLibrary, class SecondOperation,
          class Checker, class... Param>
bool RunStressTest(FirstLibrary first_library, FirstOperation first_operation,
                   SecondLibrary second_library, SecondOperation second_operation,
                   int channel_count, MinTyp from, MinTyp to, Checker checker,
                   const Param&... param) {
  constexpr int kIterCount = 50;
  constexpr int kMaxSize = 1000;

  std::mt19937 generator{42};
  std::uniform_int_distribution<int> size_distribution(1, kMaxSize);

  for (int iteration = 0; iteration < kIterCount; ++iteration) {
    auto width = size_distribution(generator);
    auto height = size_distribution(generator);

    auto input = imgprcbench::GenerateRandomImage(from, channel_count, width, height);

    auto first_output = imgprcbench::GenerateRandomImage(to, channel_count, width, height);
    auto second_output = imgprcbench::DeepCopy(*first_output);

    PerformUnaryOperation(first_library, first_operation, *first_output, *input, param...);
    PerformUnaryOperation(second_library, second_operation, *second_output, *input, param...);

    if (!checker(*first_output, *second_output)) {
      return false;
    }
  }
  return true;
}

#define BENCH_TEST(library, library_ns, operation, channel_count, from_type, to_type, eps, mult, \
                   add)                                                                          \
  TEST(STRESS_TEST, library##_##from_type##_##to_type##_##channel_count##_##operation) {         \
    auto checker = imgprcbench::ElementWiseChecker(eps);                                         \
    bool res = RunStressTest(library_ns::LibrarySuite(), library_ns::operation,                  \
                             minimg_benchmark::LibrarySuite(), minimg_benchmark::operation,      \
                             channel_count, from_type, to_type, checker, mult, add);             \
    ASSERT_TRUE(res);                                                                            \
  }

#define OPENCV_TEST(ch_count, from_type, to_type, eps, mult, add) \
  BENCH_TEST(OpenCv, opencv_benchmark, LinTransform, ch_count, from_type, to_type, eps, mult, add);

#define OPENCV_TEST_CH(from_type, to_type, eps, mult, add) \
  OPENCV_TEST(1, from_type, to_type, eps, mult, add);      \
  OPENCV_TEST(3, from_type, to_type, eps, mult, add);

constexpr double kEps = 0.0;

#define OPENCV_TEST_TYPE(mult, add)                        \
  OPENCV_TEST_CH(TYP_UINT8, TYP_INT32, kEps, mult, add);   \
  OPENCV_TEST_CH(TYP_INT32, TYP_UINT8, kEps, mult, add);   \
  OPENCV_TEST_CH(TYP_INT32, TYP_INT32, kEps, mult, add);   \
  OPENCV_TEST_CH(TYP_REAL32, TYP_REAL32, kEps, mult, add); \
  OPENCV_TEST_CH(TYP_REAL32, TYP_UINT8, kEps, mult, add);  \
  OPENCV_TEST_CH(TYP_UINT8, TYP_REAL32, kEps, mult, add);  \
  OPENCV_TEST_CH(TYP_INT32, TYP_REAL32, kEps, mult, add);  \
  OPENCV_TEST_CH(TYP_REAL32, TYP_INT32, kEps, mult, add);

OPENCV_TEST_TYPE(3.5, 2.0);

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
