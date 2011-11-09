#include "resizers_cubic.h"
#include <inttypes.h>

using namespace Bitmap;
using namespace Resizers;


void Resizers::Cubic::do_resize_x(const Channel* src, Channel* dst){
  double x_pos;
  double step = double(src->width - 1) / double(dst->width - 1);
  
  uint8_t *dst_data = dst->data;
  uint8_t *src_data = src->data;

  double prev, next;

  for(int y = 0; y < dst->height; y++){
    
    x_pos = step;
    *dst_data++ = src_data[y*src->width];

    for(int x = 1; x < dst->width-1; x++){
      prev = src_data[y*src->width + int(x_pos)];
      next = src_data[y*src->width + int(x_pos) + 1];
      *dst_data = next*(x_pos - int(x_pos)) + prev*(int(x_pos) + 1 - x_pos);
      dst_data++;
      x_pos += step;
    }

    *dst_data++ = src_data[(y+1)*src->width - 1];
  }
}

void Resizers::Cubic::do_resize_y(const Channel* src, Channel* dst){
  double step = double(src->height - 1) / double(dst->height - 1);
  
  uint8_t *dst_data = dst->data;
  uint8_t *src_data = src->data;
  
  double prev, next;

  double y_pos = step;
  int y_pos_int;
  for(int y = 0; y < dst->height-1; y++){
    y_pos_int = src->width * int(y_pos);
    for(int x = 0; x < dst->width; x++){
      prev = src_data[x + y_pos_int];
      next = src_data[x + src->width + y_pos_int];
      *dst_data = next*(y_pos - int(y_pos)) + prev*(int(y_pos) + 1 - y_pos);
      dst_data++;
    }
    y_pos += step;
  }

  // lower border
  for(int x = 0 ; x < src->width ; x++){
    *dst_data = src_data[x + src->width*(src->height-1)];
    dst_data++;
  }
}
