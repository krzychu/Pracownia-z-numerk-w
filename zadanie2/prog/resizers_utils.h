#ifndef RESIZERS_UTILS
#define RESIZERS_UTILS

#include "resizers_base.h"
#include "bitmap_image.h"

namespace Resizers{
  Resizer* get_by_name(const char* name);

  Bitmap::ResizeStats resize_xy_percent(Bitmap::Image * img, int x_percent, 
                                        int y_percent, Resizer* resizer);

  Bitmap::ResizeStats resize_yx_percent(Bitmap::Image * img, int x_percent, 
                                        int y_percent, Resizer* resize);
};

#endif
