#include <cstdio>
#include <iostream>
#include "bitmap.h"

using namespace Bitmap;

int main(){
  
  try{
    Image img("../obrazki/test2.bmp");
    std::cout << img;
  }
  catch(BitmapError err){
    std::cout << err;  
  }

  return 0;
}
