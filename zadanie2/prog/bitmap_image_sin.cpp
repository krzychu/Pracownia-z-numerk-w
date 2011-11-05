#include "bitmap_image_sin.h"
#include "bitmap_channel.h"


Bitmap::SinImage::SinImage(int w, int h){
  Channel* channel = new Channel(w,h); 
  for(int y = 0 ; y < h; y++){
    for(int x = 0; x < w; x++){
      channel->data[x + y*w] = (x+y) % 256;
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
