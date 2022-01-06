#pragma once

#include <minbase/minresult.h>
#include <minimgapi/minimgapi.h>
#include <minimgprc/minimgprc.h>
#include <minimgapi/test/minrandom.hpp>

#include <imgprcbench/utility.h>

namespace imgprcbench {

////////////////////////////////////////////////////////////////////////////////////////////////////

// Generators

////////////////////////////////////////////////////////////////////////////////////////////////////

MinImgUniquePtr GenerateResizedImage(const MinImg& initial_image, int width, int height) {
  THROW_ON_ERROR(AssureMinImageIsValid(&initial_image));

  MinImgUniquePtr image{new MinImg{}};

  THROW_ON_ERROR(CloneResizedMinImagePrototype(image.get(), &initial_image, width, height));

  THROW_ON_ERROR(ResampleMinImage(image.get(), &initial_image));

  return image;
}

MinImgUniquePtr GenerateRandomImage(MinTyp scalar_type, int channel_count, int width, int height) {
  imgprcbench::MinImgUniquePtr image{new MinImg{}};

  THROW_ON_ERROR(NewMinImagePrototype(image.get(), width, height, channel_count, scalar_type));

  THROW_ON_ERROR(ApplyLineFunctor(image.get(), Random255()));

  return image;
}

}  // namespace imgprcbench
