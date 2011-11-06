#ifndef _BITMAP_IMAGE_PROCEDURAL_
#define _BITMAP_IMAGE_PROCEDURAL_

#include "bitmap_image.h"

namespace Bitmap{
  BWImage* sinImage(int w, int h);
  BWImage* sawImage(int w, int h);
  BWImage* rungeImage(int w, int h);
};

#endif
