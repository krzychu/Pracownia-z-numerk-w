#include "resizers_closest.h"
#include <inttypes.h>

using namespace Bitmap;
using namespace Resizers;


void Resizers::Closest::do_resize_x(const Channel* src, Channel* dst){
  double x_pos;
  double step = double(src->width - 1) / double(dst->width - 1);
  uint8_t *dst_data = dst->data;
  uint8_t *src_data = src->data;
  for(int y = 0; y < dst->height; y++){
    x_pos = 0;
    for(int x = 0; x < dst->width; x++){
      *dst_data = src_data[y*src->width + round(x_pos)];
      dst_data++;
      x_pos += step;
    }
  }
}

void Resizers::Closest::do_resize_y(const Channel* src, Channel* dst){
  double y_pos = 0;
  double step = double(src->height - 1) / double(dst->height - 1);
  uint8_t *dst_data = dst->data;
  uint8_t *src_data = src->data;
  for(int y = 0; y < dst->height; y++){
    for(int x = 0; x < dst->width; x++){
      *dst_data = src_data[x + src->width * round(y_pos)];
      dst_data++;
    }
    y_pos += step;
  }
}
