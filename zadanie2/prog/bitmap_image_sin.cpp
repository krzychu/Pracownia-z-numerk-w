#include "bitmap_image_sin.h"
#include "bitmap_channel.h"

#include <cmath>

Bitmap::SinImage::SinImage(int w, int h){
  Channel* channel = new Channel(w,h); 
  double fx = 10.0 * M_PI / double(w);
  double fy = 10.0 * M_PI / double(h);
  for(int y = 0 ; y < h; y++){
    for(int x = 0; x < w; x++){
      channel->data[x + y*w] = 128 + sin(fy*double(y))*sin(fx*double(x))*127;
    }
  }

  isMono = true;
  red = NULL;
  green = NULL;
  blue = NULL;
  gray = channel;

  width = w;
  height = h;

}
