#ifndef _RESIZERS_H_
#define _RESIZERS_H_

#include "bitmap_image.h"

namespace Resizers{
  
  class AbstractResizer{
    private:
      long start_time;

    protected:
      resize_x  

    public:
      long resize_x(const Channel* src, Channel* dst);
      long resize_y(const Channel* src, Channel* dst);
  };

};

#endif
