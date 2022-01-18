#pragma once

#include <memory>

#include <minbase/minimg.h>
#include <minimgapi/minimgapi.h>
#include <minimgapi/test/minrandom.hpp>

struct MinImgDeleter {
  void operator()(MinImg* image) {
    if (image != nullptr) {
      THROW_ON_ERROR(FreeMinImage(image));
    }
    delete image;
  }
};

using Image = std::unique_ptr<MinImg, MinImgDeleter>;

inline Image RandomImage(MinTyp scalar_type, int channel_count, int width,
                         int height) {
  Image image{new MinImg{}};

  THROW_ON_ERROR(NewMinImagePrototype(image.get(), width, height, channel_count,
                                      scalar_type));

  THROW_ON_ERROR(ApplyLineFunctor(image.get(), Random255()));

  return image;
}
