#include "resizers_combined.h"

using namespace Bitmap;

Resizers::Combined::Combined(){
  cubic = new Cubic();
  linear = new Linear();
}

Resizers::Combined::~Combined(){
  delete cubic;
  delete linear;
}

void Resizers::Combined::do_resize_x(const Channel* src, Channel* dst){
  if(src->width > dst->width)
    linear->do_resize_x(src, dst);
  else
    cubic->do_resize_x(src, dst);
}

void Resizers::Combined::do_resize_y(const Channel* src, Channel* dst){
  if(src->height > dst->height)
    linear->do_resize_y(src, dst);
  else
    cubic->do_resize_y(src, dst);
}
