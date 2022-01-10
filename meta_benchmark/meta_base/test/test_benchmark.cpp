#include <random>
#include <string>
#include <vector>

#include <meta_base.h>

template <class Arithmetic>
using Matrix = std::vector<std::vector<Arithmetic>>;

template <class Arithmetic>
Matrix<Arithmetic> GenerateMatrix(int w, int h) {
  Matrix<Arithmetic> result(h, std::vector<Arithmetic>(w));

  static std::mt19937 gen;

  std::uniform_int_distribution<int> dist{0, 255};

  for (auto& row : result) {
    for (auto& val : row) {
      val = static_cast<Arithmetic>(dist(gen));
    }
  }

  return result;
}

template <class S, class D>
void LinTransform(const Matrix<S>& source, Matrix<D>& dest) {
  for (int i = 0; i < source.size(); ++i) {
    for (int j = 0; j < source[i].size(); ++j) {
      dest[i][j] = static_cast<S>(source[i][j]);
    }
  }
}

using Map = std::map<std::string, std::string>;

int main(int argc, char* argv[]) {
  meta_mark::GenerateGrid(
      [](size_t w, size_t h) {
        using Pair = std::pair<Matrix<int>, Matrix<double>>;
        auto gen = [=]() {
          return std::make_pair(GenerateMatrix<int>(w, h),
                                GenerateMatrix<double>(w, h));
        };
        auto op = [](Pair& pair) {
          LinTransform(pair.first, pair.second);
        };
        meta_mark::AddMetaBenchmark(
            Map{{"w", std::to_string(w)}, {"h", std::to_string(h)}}, gen, op);
      },
      {1, 2, 4, 8, 16, 32, 64}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

  meta_mark::Run(argc, argv);

  return 0;
}
