#ifndef _RESIZERS_COMBINED_H_
#define _RESIZERS_COMBINED_H_

#include "resizers_base.h"
#include "resizers_cubic.h"
#include "resizers_linear.h"

namespace Resizers{
  
  class Combined : public Resizer{
    private:
      Cubic* cubic;
      Linear* linear;
    
    protected:
      virtual void do_resize_x(const Bitmap::Channel* src, 
         Bitmap::Channel* dst) ;
      virtual void do_resize_y(const Bitmap::Channel* src, 
         Bitmap::Channel* dst) ;

    public:
      Combined();
      ~Combined();
  };

};

#endif
