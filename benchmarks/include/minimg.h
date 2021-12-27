#pragma once

#include <minbase/minimg.h>
#include <minimgapi/minimgapi.h>
#include <minimgprc/minimgprc.h>
#include <minimgapi/imgguard.hpp>

#include <imgprcbench/utility.h>

namespace minimg_benchmark {

////////////////////////////////////////////////////////////////////////////////////////////////////

class LibrarySuite {
 public:
  std::unique_ptr<MinImg> HeaderConvert(const MinImg& image) {
    return std::make_unique<MinImg>(image);
  }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

// MinImg binary operations

////////////////////////////////////////////////////////////////////////////////////////////////////

void BinarySum(MinImg& output, const MinImg& first, const MinImg& second) {
  THROW_ON_ERROR(MergeImage(&output, &first, &second, BIOP_ADD));
}

void BinaryDifference(MinImg& output, const MinImg& first, const MinImg& second) {
  THROW_ON_ERROR(MergeImage(&output, &first, &second, BIOP_DIF));
}

void BinaryAbsoluteDifference(MinImg& output, const MinImg& first, const MinImg& second) {
  THROW_ON_ERROR(MergeImage(&output, &first, &second, BIOP_ADF));
}

void BinaryMultiplication(MinImg& output, const MinImg& first, const MinImg& second) {
  THROW_ON_ERROR(MergeImage(&output, &first, &second, BIOP_MUL));
}

void BinaryDivision(MinImg& output, const MinImg& first, const MinImg& second) {
  THROW_ON_ERROR(MergeImage(&output, &first, &second, BIOP_DIV));
}

void BinaryPow(MinImg& output, const MinImg& first, const MinImg& second) {
  THROW_ON_ERROR(MergeImage(&output, &first, &second, BIOP_POW));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// MinImg unary operations

////////////////////////////////////////////////////////////////////////////////////////////////////

void UnaryAbs(MinImg& output, const MinImg& input) {
  THROW_ON_ERROR(OperateImageUnary(&output, &input, UNOP_ABS));
}

void UnarySqrt(MinImg& output, const MinImg& input) {
  THROW_ON_ERROR(OperateImageUnary(&output, &input, UNOP_SQRT));
}

void LinTransform(MinImg& output, const MinImg& input, double mul, double add) {
  THROW_ON_ERROR(LinTransformImage(&output, &input, mul, add, PC_MEDIUM));
}

void ConvertImage(MinImg& output, const MinImg& input) {
  THROW_ON_ERROR(ConvertImage(&output, &input));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// MinImg unary operation with a number

////////////////////////////////////////////////////////////////////////////////////////////////////

void UnaryAdd(MinImg& output, const MinImg& input, double value) {
  THROW_ON_ERROR(LinTransformImage(&output, &input, 1, value));  // Change to MergeImage
}

void UnaryAbsoluteDifference(MinImg& output, const MinImg& input, double value) {  // Doesn't work
  MinImg scalar{};
  THROW_ON_ERROR(WrapScalarWithMinImage(&scalar, &value, TYP_REAL64));
  THROW_ON_ERROR(MergeImage(&output, &input, &scalar, BIOP_ADF));
}

void UnaryMultiplication(MinImg& output, const MinImg& input, double value) {
  THROW_ON_ERROR(LinTransformImage(&output, &input, value, 0));  // Change to MergeImage
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// MinImg unary operations with channel

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////

// MinImg linear filter

////////////////////////////////////////////////////////////////////////////////////////////////////

void AverFilter(MinImg& output, const MinImg& input, int hor_wing, int ver_wing) {
  THROW_ON_ERROR(AverFilterImage(&output, &input, hor_wing, ver_wing, BorderOption::BO_REPEAT));
}

void GaussFilter(MinImg& output, const MinImg& input, double sigma) {
  THROW_ON_ERROR(GaussFilterImage(&output, &input, sigma, sigma, BorderOption::BO_REPEAT));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// MinImg transpose

////////////////////////////////////////////////////////////////////////////////////////////////////

void Transpose(MinImg& output, const MinImg& input) {
  THROW_ON_ERROR(TransposeMinImage(&output, &input));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// MinImg scale

////////////////////////////////////////////////////////////////////////////////////////////////////

void ScaleSubPixel(MinImg& output, const MinImg& input) {
  THROW_ON_ERROR(ScaleImage(&output, &input, QualityOption::QO_SUBPIXEL));
}

void ScalePixel(MinImg& output, const MinImg& input) {
  THROW_ON_ERROR(ScaleImage(&output, &input, QualityOption::QO_PIXEL));
}

}  // namespace minimg_benchmark
