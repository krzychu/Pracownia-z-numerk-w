#include "bitmap.h"
#include <iostream>

using namespace Bitmap;

int main(){
  try{
    SinImage sin(200,200);
    sin.save("../obrazki/sin_test.bmp");
  }
  catch(BitmapError e){
    std::cout << e;
  }
}
