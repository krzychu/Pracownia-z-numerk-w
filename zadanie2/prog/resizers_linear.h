#ifndef _RESIZERS_LINEAR_H_
#define _RESIZERS_LINEAR_H_

#include "resizers_base.h"

namespace Resizers{
  
  class Linear : public Resizer{
    protected:
      virtual void do_resize_x(const Bitmap::Channel* src, 
         Bitmap::Channel* dst) ;
      virtual void do_resize_y(const Bitmap::Channel* src, 
         Bitmap::Channel* dst) ;
  };
};

#endif
