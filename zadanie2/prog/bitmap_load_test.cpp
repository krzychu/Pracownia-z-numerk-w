#include <cstdio>
#include <iostream>
#include "bitmap.h"

using namespace Bitmap;

int main(){
  
  try{
    RGBImage* img = (RGBImage*)Image::load("../obrazki/test2.bmp");
    std::cout << *img;
    delete img;
  }
  catch(BitmapError err){
    std::cout << err;  
  }

  return 0;
}
