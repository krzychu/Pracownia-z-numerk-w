#include "resizers_base.h"
#include <sys/time.h>


using namespace Resizers;
using namespace Bitmap;

long Resizers::Resizer::get_time(){
  timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + 1000000*tv.tv_sec;
}

void Resizers::Resizer::start_timer(){
  start_time = get_time();
}

long Resizers::Resizer::stop_timer(){
  return get_time() - start_time;
}


Result Resizers::Resizer::resize_x(const Channel* src, int new_width){
  Result res;
  res.channel = new Channel(new_width, src->height);
  start_timer();
  do_resize_x(src, res.channel);
  res.time = stop_timer();
  return res;
}

Result Resizers::Resizer::resize_y(const Channel* src, int new_height){
  Result res;
  res.channel = new Channel(src->width, new_height);
  start_timer();
  do_resize_y(src, res.channel);
  res.time = stop_timer();
  return res;
}
