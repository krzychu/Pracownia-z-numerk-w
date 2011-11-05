#ifndef _BITMAP_IMAGE_PROCEDURAL_
#define _BITMAP_IMAGE_PROCEDURAL_

#include "bitmap_image.h"

namespace Bitmap{
  
  class SinImage : public Image{
    public:
      SinImage(int w, int h);
  };

  class SawImage : public Image{
    public:
      SawImage(int w, int h);
  };

  class RungeImage : public Image{
    public:
      RungeImage(int w, int h);
  };

};

#endif
