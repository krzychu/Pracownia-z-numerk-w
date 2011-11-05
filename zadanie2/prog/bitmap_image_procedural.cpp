#include "bitmap_image_procedural.h"
#include "bitmap_channel.h"

#include <cmath>

Bitmap::SinImage::SinImage(int w, int h){
  Channel* channel = new Channel(w,h); 
  double fx = 10.0 * M_PI / double(w-1);
  double fy = 10.0 * M_PI / double(h-1);
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


Bitmap::SawImage::SawImage(int w, int h){
  Channel* channel = new Channel(w,h); 
  double fx = 1000.0 / double(w-1);
  double fy = 1000.0 / double(h-1);
  for(int y = 0 ; y < h; y++){
    for(int x = 0; x < w; x++){
      channel->data[x + y*w] = int(fx*double(x) + fy*double(y)) % 256;
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

Bitmap::RungeImage::RungeImage(int w, int h){
  Channel* channel = new Channel(w,h); 
  double fx = 5.0 / double(w-1);
  double fy = 5.0 / double(h-1);
  for(int y = 0 ; y < h; y++){
    for(int x = 0; x < w; x++){
      double x2 = fx*double(x) - 2.5;
      x2 *= x2;

      double y2 = fy*double(y) - 2.5;
      y2 *= y2;
 
      channel->data[x + y*w] = 255.0 / (1.0 + x2 + y2);
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
