#include <cstdio>
#include <iostream>
#include "bitmap.h"

using namespace Bitmap;

int main(){
  
  try{
    load("../obrazki/test2.bmp");
  }
  catch(BitmapError err){
    std::cout << err;  
  }

  return 0;
}
