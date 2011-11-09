#ifndef _RESIZERS_CUBIC_H_
#define _RESIZERS_CUBIC_H_

#include "resizers_base.h"

namespace Resizers{
  
  class Cubic : public Resizer{
    protected:
      virtual void do_resize_x(const Bitmap::Channel* src, 
         Bitmap::Channel* dst) ;
      virtual void do_resize_y(const Bitmap::Channel* src, 
         Bitmap::Channel* dst) ;
  };
};

#endif
