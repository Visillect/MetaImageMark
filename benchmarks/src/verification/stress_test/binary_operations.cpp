#include <random>

#include <gtest/gtest.h>

#include <imgprcbench/checkers.h>
#include <imgprcbench/generators.h>
#include <imgprcbench/utility.h>
#include <imgprcbench/verification.h>

#include <minimg.h>
#include <opencv.h>

using imgprcbench::PerformBinaryOperation;

template <class FirstLibrary, class FirstOperation, class SecondLibrary, class SecondOperation,
          class Checker>
void RunStressTest(FirstLibrary first_library, FirstOperation first_operation,
                   SecondLibrary second_library, SecondOperation second_operation,
                   int channel_count, MinTyp type, Checker checker) {
  constexpr int kIterCount = 50;
  constexpr int kMaxSize = 1000;

  std::mt19937 generator{42};
  std::uniform_int_distribution<int> size_distribution(1, kMaxSize);

  for (int iteration = 0; iteration < kIterCount; ++iteration) {
    auto width = size_distribution(generator);
    auto height = size_distribution(generator);

    auto first_img = imgprcbench::GenerateRandomImage(type, channel_count, width, height);
    auto second_img = imgprcbench::GenerateRandomImage(type, channel_count, width, height);

    auto first_output = imgprcbench::GenerateRandomImage(type, channel_count, width, height);
    auto second_output = imgprcbench::DeepCopy(*first_output);

    PerformBinaryOperation(first_library, first_operation, *first_output, *first_img, *second_img);
    PerformBinaryOperation(second_library, second_operation, *second_output, *first_img,
                           *second_img);

    ASSERT_TRUE(checker(*first_output, *second_output)) << "Iteration: " << iteration;
  }
}

#define BENCH_TEST(library, library_ns, operation, channel_count, type, eps)                    \
  TEST(STRESS_TEST, library##_##type##_##channel_count##_##operation) {                         \
    auto checker = imgprcbench::ElementWiseChecker(eps);                                        \
    RunStressTest(library_ns::LibrarySuite(), library_ns::operation,                            \
                  minimg_benchmark::LibrarySuite(), minimg_benchmark::operation, channel_count, \
                  type, checker);                                                               \
  }

#define OPENCV_TEST(ch_count, type, eps)                                               \
  BENCH_TEST(OpenCv, opencv_benchmark, BinarySum, ch_count, type, eps);                \
  BENCH_TEST(OpenCv, opencv_benchmark, BinaryDifference, ch_count, type, eps);         \
  BENCH_TEST(OpenCv, opencv_benchmark, BinaryAbsoluteDifference, ch_count, type, eps); \
  BENCH_TEST(OpenCv, opencv_benchmark, BinaryMultiplication, ch_count, type, eps);

#define OPENCV_TEST_CH(type, eps) \
  OPENCV_TEST(1, type, eps);      \
  OPENCV_TEST(3, type, eps);

OPENCV_TEST_CH(TYP_UINT8, 0);
OPENCV_TEST_CH(TYP_INT32, 0);
OPENCV_TEST_CH(TYP_REAL32, 0.005);

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
