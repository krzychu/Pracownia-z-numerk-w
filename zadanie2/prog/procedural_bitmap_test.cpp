#include "bitmap.h"
#include <iostream>

using namespace Bitmap;

int main(){
  try{
    SinImage sin(200,200);
    sin.save("../obrazki/sin_test.bmp");
    
    SawImage saw(200,200);
    saw.save("../obrazki/saw_test.bmp");
   
    RungeImage runge(200,200);
    runge.save("../obrazki/runge_test.bmp");
  

  }
  catch(BitmapError e){
    std::cout << e;
  }
}
