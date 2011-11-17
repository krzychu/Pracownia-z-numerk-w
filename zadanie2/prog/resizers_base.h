#ifndef _RESIZERS_BASE_H_
#define _RESIZERS_BASE_H_

#include "bitmap_channel.h"


namespace Resizers{
 
  struct Result{
    long time;
    Bitmap::Channel* channel;
  };

  class Resizer{
    private:
      long start_time;
      
      void start_timer();
      long stop_timer();
      long get_time();
    
    protected:
      inline int round(double x){
        return int(x + 0.5);
      }

      virtual void do_resize_x(const Bitmap::Channel* src, 
         Bitmap::Channel* dst) = 0;
      virtual void do_resize_y(const Bitmap::Channel* src, 
         Bitmap::Channel* dst) = 0;

    public:
      Result resize_x(const Bitmap::Channel* src, int new_width);
      Result resize_y(const Bitmap::Channel* src, int new_height);
  };


};

#endif
