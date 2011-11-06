#include "bitmap.h"
#include <iostream>

using namespace Bitmap;

int main(){
  try{
    Image* sin = sinImage(200,200);
    sin->save("../obrazki/sin_test.bmp");

    Image* saw = sawImage(200,200);
    saw->save("../obrazki/saw_test.bmp");
    
    Image* runge = rungeImage(200,200);
    runge->save("../obrazki/runge_test.bmp");

    delete sin;
    delete saw;
    delete runge;
  }
  catch(BitmapError e){
    std::cout << e;
  }
}
