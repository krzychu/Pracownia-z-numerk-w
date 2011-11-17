#include <cstring>
#include "resizers.h"

using namespace Resizers;
using namespace Bitmap;


Resizer* Resizers::get_by_name(const char* name){
  Resizer* resizer = NULL;
  if(0 == strcmp(name, "closest")){
    resizer = new Closest();
  }
  else if(0 == strcmp(name, "linear")){
    resizer = new Linear();
  }
  else if(0 == strcmp(name, "cubic")){
    resizer = new Cubic();
  }
  else if(0 == strcmp(name, "combined")){
    resizer = new Combined();
  }
  return resizer;
}


ResizeStats Resizers::resize_xy_percent(Image * img, int x_percent, 
  int y_percent, Resizer* resizer)
{
  ResizeStats rs,rs2;
  rs = img->resize_x_percent(x_percent, resizer);
  rs2 = rs.img->resize_y_percent(y_percent, resizer);
  delete rs.img;
  rs2.time += rs.time;
  return rs2;
}


ResizeStats Resizers::resize_yx_percent(Image * img, int x_percent, 
  int y_percent, Resizer* resizer)
{
  ResizeStats rs,rs2;
  rs = img->resize_y_percent(y_percent, resizer);
  rs2 = rs.img->resize_x_percent(x_percent, resizer);
  delete rs.img;
  rs2.time += rs.time;
  return rs2;
}


